/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/28 19:51:14 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophers(void *philo)
{
	t_philo	*ph;
	t_args	*a;

	ph = (t_philo *)philo;
	a = ph->args;
	if (ph->n % 2)
		usleep(a->die_tm * 0.25);
	while (1)
	{
		if (ph->n % 2 && ph->ate)
			usleep(a->die_tm * 0.25);
		if (a->phi_nb == 1)
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
	t_philo			*ph;
	int				eat;

	ph = (*(t_philo **)philos);
	while (1)
	{
		i = -1;
		while (++i < ph[0].args->phi_nb)
		{
			if (born_to_kill(ph, i))
				return (NULL);
		}
		if (pthread_mutex_lock(&ph->args->keeper))
			ft_puterror(FAILED_MUTEX_LOCK);
		eat = ph->args->plate;
		if (pthread_mutex_unlock(&ph->args->keeper))
			ft_puterror(FAILED_MUTEX_UNLOCK);
		if (eat == ph->args->phi_nb)
			return (NULL);
		usleep(50);
	}
	return (NULL);
}

int	born_to_kill(t_philo *ph, int i)
{
	long			time;

	if (pthread_mutex_lock(&ph->args->death[i].death))
		ft_puterror(FAILED_MUTEX_LOCK);
	time = ft_utdiff(get_time(),
			convert_time(ph->args->death[i].last_meal));
	if (pthread_mutex_unlock(&ph->args->death[i].death))
		ft_puterror(FAILED_MUTEX_UNLOCK);
	if (time >= ph->args->die_tm || ph->args->exec)
	{
		if (pthread_mutex_lock(&ph->args->keeper))
			ft_puterror(FAILED_MUTEX_LOCK);
		ph->args->one_died = 1;
		if (pthread_mutex_unlock(&ph->args->keeper))
			ft_puterror(FAILED_MUTEX_UNLOCK);
		if (pthread_mutex_lock(&ph->args->print))
			ft_puterror(FAILED_MUTEX_LOCK);
		printf("[%ld] %d %s", get_time() - ph->args->start, ph->n + 1,
			"died\n");
		if (pthread_mutex_unlock(&ph->args->print))
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
		philos = malloc(sizeof(*philos) * args.phi_nb);
		if (philos == NULL)
			free_args(&args, FAILED_MALLOC | FREE_ALL);
		flag = exec_threads(&args, philos);
		free(philos);
		free_args(&args, FREE_ALL | DESTROY_ALL);
	}
	return (flag);
}
