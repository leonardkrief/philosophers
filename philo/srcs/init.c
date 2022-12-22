/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/22 06:05:41 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args_stack(t_args *args, int ac, char **av)
{
	args->phi_nb = ft_atoi_ph(av[1]);
	args->die_tm = ft_atoi_ph(av[2]);
	args->eat_tm = ft_atoi_ph(av[3]) * 1000;
	args->slp_tm = ft_atoi_ph(av[4]) * 1000;
	if (ac == 6)
		args->eat_nb = ft_atoi_ph(av[5]);
	else
		args->eat_nb = 0;
	args->exec = 0;
	args->dead = 0;
	args->start.tv_sec = 0;
	args->start.tv_usec = 0;
	args->th = NULL;
	args->fork = NULL;
	args->mutex = NULL;
}

int	init_args_heap(t_args *args)
{
	int	i;

	if (pthread_mutex_init(&args->safety, NULL))
		return (free_args(args, FAILED_INIT_MUTEX));
	args->th = malloc (sizeof(*args->th) * (args->phi_nb));
	if (args->th == NULL)
		return (free_args(args, FAILED_MALLOC));
	args->fork = ft_calloc ((args->phi_nb), sizeof(*args->fork));
	if (args->fork == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS));
	memset(args->fork, 1, args->phi_nb);
	args->mutex = malloc (sizeof(*args->mutex) * args->phi_nb);
	if (args->mutex == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS | FREE_FORKS));
	i = -1;
	while (++i < (int)args->phi_nb)
	{
		if (pthread_mutex_init(&args->mutex[i], NULL))
		{
			while (--i >= 0)
				pthread_mutex_destroy(&args->mutex[i]);
			return (free_args(args, FAILED_INIT_MUTEX | FREE_ALL));
		}
	}
	return (0);
}

int	init_philo(t_args *args, t_philo *philo, int i)
{
	philo->args = args;
	philo->n = i;
	philo->ate = 0;
	philo->eating = 0;
	philo->dead = 0;
	if (gettimeofday(&philo->last_meal, NULL))
		return (FAILED_GET_TIME);
	return (0);
}

int	exec_threads(t_args *args, t_philo *philos)
{
	unsigned int	i;
	unsigned int	x;

	if (gettimeofday(&args->start, NULL))
		args->exec += 1;
	if (pthread_mutex_lock(&args->safety))
		return (free_args(args, FAILED_MUTEX_LOCK | FREE_ALL | DESTROY_ALL));
	i = -1;
	while (++i < args->phi_nb && !args->exec)
	{
		if (init_philo(args, &philos[i], i) 
			|| pthread_create(&args->th[i], NULL, &philosophers, &philos[i]))
			args->exec += 2;
	}
	if (pthread_mutex_unlock(&args->safety))
		args->exec += 4;
	x = 0;
	while (x < i)
	{
		if (pthread_join(args->th[x++], NULL))
			args->exec += 8;
	}
	return (args->exec);
}
