/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/26 02:49:30 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophers(void *philo)
{
	t_philo	*ph;
	t_args	*a;

	ph = (t_philo *)philo;
	a = ph->args;
	while (1)
	{
		if (a->phi_nb % 2 && ph->ate)
			ft_usleep(ph->args->die_tm * 0.25);
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
	unsigned int	i;
	t_philo			*ph;
	long			time;
	unsigned int	eat;

	ph = (*(t_philo **)philos);
	while (1)
	{
		i = -1;
		while (++i < ph[0].args->phi_nb)
		{
			if (pthread_mutex_lock(&ph->args->death[i].death))
				ft_puterror(FAILED_MUTEX_LOCK);
			time = ft_utdiff(get_time(),
					convert_time(ph->args->death[i].last_meal));
			if (pthread_mutex_unlock(&ph->args->death[i].death))
				ft_puterror(FAILED_MUTEX_UNLOCK);
			if (time >= ph->args->die_tm)
			{
				pthread_mutex_lock(&ph->args->keeper);
				ph->args->one_died = 1;
				pthread_mutex_unlock(&ph->args->keeper);
				pthread_mutex_lock(&ph->args->print);
				printf("[%ld] %d %s", get_time() - ph->args->start, ph->n + 1,
						"died\n");
				pthread_mutex_unlock(&ph->args->print);
				return (NULL);
			}
		}
		pthread_mutex_lock(&ph->args->keeper);
		eat = ph->args->plate;
		pthread_mutex_unlock(&ph->args->keeper);
		if (eat == ph->args->phi_nb)
			return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	*philos;
	int		flag;

	flag = 0;
	if (ac <= 4)
		ft_putstr_fd("Too few arguments\n", 2);
	else if (ac >= 7)
		ft_putstr_fd("Too much arguments\n", 2);
	else if (ft_atoi_ph(av[1]) <= 1)
		ft_putstr_fd("Not enough philosophers\n", 2);
	else
	{
		init_args_stack(&args, ac, av);
		if (init_args_heap(&args) != 0)
			return (-1);
		philos = malloc(sizeof(*philos) * args.phi_nb);
		if (philos == NULL)
			free_args(&args, FAILED_MALLOC | FREE_ALL);
		flag = exec_threads(&args, philos);
		// free(philos);
		// free_args(&args, FREE_ALL | DESTROY_ALL);
	}
	return (flag);
}
