/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/31 02:16:55 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args_stack(t_args *args, int ac, char **av)
{
	memset(args, 0, sizeof(*args));
	args->total = ft_atoi_ph(av[1]);
	args->die_timer = ft_atoi_ph(av[2]) * 1000;
	args->eat_timer = ft_atoi_ph(av[3]);
	args->slp_timer = ft_atoi_ph(av[4]);
	if (ac == 6)
		args->max_eat = ft_atoi_ph(av[5]);
	if (args->total < 0 || args->max_eat < 0 || args->die_timer < 0
		|| args->eat_timer < 0 || args->slp_timer < 0)
		return (1);
	return (0);
}

int	init_args_heap(t_args *args)
{
	args->thread = malloc(sizeof(*args->thread) * (args->total + 1));
	if (args->thread == NULL)
		return (free_args(args, FAILED_MALLOC));
	args->fork = malloc(sizeof(*args->fork) * args->total);
	if (args->fork == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS));
	memset(args->fork, 1, args->total);
	args->mut_fork = malloc(sizeof(*args->mut_fork) * args->total);
	if (args->mut_fork == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS | FREE_FORKS));
	args->death = malloc(sizeof(*args->death) * args->total);
	if (args->death == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS | FREE_FORKS
				| FREE_MUTEX_FORKS));
	if (pthread_mutex_init(&args->print, NULL))
		return (free_args(args, FAILED_INIT_MUTEX | FREE_ALL));
	if (pthread_mutex_init(&args->keeper, NULL))
		return (free_args(args, FAILED_INIT_MUTEX | FREE_ALL
				| DESTROY_MUT_PRINT));
	return (init_args_heap_2(args));
}

int	init_args_heap_2(t_args *args)
{
	int				i;
	char			free;

	free = 0;
	i = -1;
	while (!free && ++i < args->total)
	{
		if (!free && pthread_mutex_init(&args->mut_fork[i], NULL))
			free = 1;
		while (free && --i)
			pthread_mutex_destroy(&args->mut_fork[i]);
	}
	i = -1;
	while (!free && ++i < args->total)
	{
		if (!free && pthread_mutex_init(&args->death[i], NULL))
			free = 1;
		while (free && --i)
			pthread_mutex_destroy(&args->death[i]);
	}
	if (free)
		return (free_args(args, FAILED_INIT_MUTEX | FREE_ALL
				| DESTROY_MUT_PRINT | DESTROY_MUT_KEEPER));
	return (0);
}

int	init_philo(t_args *args, t_philo *philo, int i)
{
	memset(philo, 0, sizeof(*philo));
	philo->args = args;
	philo->id = i;
	philo->death = *(args->death);
	philo->last_meal = args->init_time;
	return (0);
}

int	exec_threads(t_args *args, t_philo *philos)
{
	int				error;
	int				i;

	error = 0;
	if (gettimeofday(&args->init_time, NULL))
		return (free_args(args, FAILED_GET_TIME | FREE_ALL | DESTROY_ALL));
	i = -1;
	while (!error && ++i < args->total)
	{
		if (init_philo(args, &philos[i], i) || pthread_create(&args
				->thread[i], NULL, &philosophers, &philos[i]))
			error = setexec_puterror(args, i - 1, FAILED_CRT_THRD);
	}
	if (pthread_create(&args->thread[args->total],
			NULL, &check_deaths, philos))
		error = setexec_puterror(args, i, FAILED_CRT_THRD);
	i = 0;
	while (i < (args->total + 1) * (!error) + error * (error != 0))
	{
		if (pthread_join(args->thread[i++], NULL))
			ft_puterror(FAILED_JOIN_THRD);
	}
	return (error);
}
