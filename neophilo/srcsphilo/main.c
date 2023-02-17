/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/02 15:42:37 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophers(void *philo)
{
	t_philo	*ph;
	t_args	*a;

	ph = (t_philo *)philo;
	a = ph->args;
	if (ph->id % 2)
		ft_usleep(a->eat_timer * 0.7);
	while (1)
	{
		if (a->total % 2 && ph->ate)
			ft_usleep(a->die_timer / 1000 * 0.25);
		if (a->total == 1)
			printlock(ph, "has taken a fork\n", 0);
		while ((!ph->l_fork || !ph->r_fork) && !died(ph))
			gets_forks(ph);
		if (eats(ph))
			break ;
		if (sleeps(ph))
			break ;
		if (printlock(ph, "is thinking\n", 0))
			break ;
	}
	return (NULL);
}

void	*check_deaths(void *philos)
{
	int				i;
	int				eat;
	t_args			*a;
	t_philo			*ph;

	ph = ((t_philo *)philos);
	a = ph[0].args;
	while (1)
	{
		i = -1;
		while (++i < a->total)
		{
			if (born_to_kill(&ph[i]))
				return (NULL);
		}
		if (pthread_mutex_lock(&a->keeper))
			ft_puterror(FAILED_MUTEX_LOCK);
		eat = a->done;
		if (pthread_mutex_unlock(&a->keeper))
			ft_puterror(FAILED_MUTEX_UNLOCK);
		if (eat == a->total)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	born_to_kill(t_philo *ph)
{
	long			time;
	t_args			*a;

	a = ph->args;
	if (pthread_mutex_lock(&ph->death))
		ft_puterror(FAILED_MUTEX_LOCK);
	time = get_time_us() - convert_time_us(ph->last_meal);
	if (pthread_mutex_unlock(&ph->death))
		ft_puterror(FAILED_MUTEX_UNLOCK);
	if (time >= a->die_timer)
	{
		if (pthread_mutex_lock(&a->keeper))
			ft_puterror(FAILED_MUTEX_LOCK);
		a->died = 1;
		if (pthread_mutex_unlock(&a->keeper))
			ft_puterror(FAILED_MUTEX_UNLOCK);
		if (pthread_mutex_lock(&a->print))
			ft_puterror(FAILED_MUTEX_LOCK);
		printf("%06ld %d %s", get_time() - convert_time(a->init_time),
			ph->id + 1, "died\n");
		if (pthread_mutex_unlock(&a->print))
			ft_puterror(FAILED_MUTEX_UNLOCK);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	*philos;
	int		flag;

	flag = 0;
	if (ac <= 4 || ac >= 7 || init_args_stack(&args, ac, av))
	{
		ft_putstr_fd("usage:\n\t./philo {nb_philos} {die_tm}", 2);
		ft_putstr_fd(" {eat_tm} {sleep_tm} (max_eat)\n", 2);
		ft_putstr_fd("\tinputs in ms is capped to 60,000 ms\n", 2);
	}
	else
	{
		if (init_args_heap(&args) != 0)
			return (-1);
		philos = malloc(sizeof(*philos) * args.total);
		if (philos == NULL)
			free_args(&args, FAILED_MALLOC | FREE_ALL);
		flag = exec_threads(&args, philos);
		free(philos);
		free_args(&args, FREE_ALL | DESTROY_ALL);
	}
	return (flag);
}
