/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/26 22:14:48 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args_stack(t_args *args, int ac, char **av)
{
	memset(args, 0, sizeof(*args));
	args->phi_nb = ft_atoi_ph(av[1]);
	args->die_tm = ft_atoi_ph(av[2]);
	args->eat_tm = ft_atoi_ph(av[3]);
	args->slp_tm = ft_atoi_ph(av[4]);
	if (ac == 6)
		args->eat_nb = ft_atoi_ph(av[5]);
}

int	init_args_heap_1(t_args *args)
{
	args->th = malloc(sizeof(*args->th) * (args->phi_nb + 1));
	if (args->th == NULL)
		return (free_args(args, FAILED_MALLOC));
	args->fork = malloc(sizeof(*args->fork) * args->phi_nb);
	if (args->fork == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS));
	memset(args->fork, 1, args->phi_nb);
	args->mutex = malloc(sizeof(*args->mutex) * args->phi_nb);
	if (args->mutex == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS | FREE_FORKS));
	args->death = malloc(sizeof(*args->death) * args->phi_nb);
	if (args->death == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS | FREE_FORKS
			| FREE_MUTEX_FORKS));
	if (pthread_mutex_init(&args->print, NULL))
		return (free_args(args, FAILED_INIT_MUTEX | FREE_THREADS | FREE_FORKS
			| FREE_MUTEX_FORKS | FREE_DEATH));
	if (pthread_mutex_init(&args->keeper, NULL))
		return (free_args(args, FAILED_INIT_MUTEX | FREE_THREADS | FREE_FORKS
			| FREE_MUTEX_FORKS | FREE_DEATH | DESTROY_MUT_PRINT));
	return (0);
}

int	init_args_heap_2(t_args *args)
{
	unsigned int	i;
	char			free;

	free = 0;
	i = -1;
	while (!free && ++i < args->phi_nb)
	{
		if (!free && pthread_mutex_init(&args->mutex[i], NULL))
			free = 1;
		while (!free && --i)
			pthread_mutex_destroy(&args->mutex[i]);
	}
	i = -1;
	while (!free && ++i < args->phi_nb)
	{
		if (!free && pthread_mutex_init(&args->death[i].death, NULL))
			free = 1;
		while (!free && --i)
			pthread_mutex_destroy(&args->death[i].death);
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
	philo->n = i;
	philo->death = &args->death[i].death;
	if (gettimeofday(&args->death[i].last_meal, NULL))
		return (FAILED_GET_TIME);
	return (0);
}

int	exec_threads(t_args *args, t_philo *philos)
{
	unsigned int	i;
	unsigned int	x;

	args->start = get_time();
	i = -1;
	while (++i < args->phi_nb && !args->exec)
	{
		init_philo(args, &philos[i], i);
		pthread_create(&args->th[i], NULL, &philosophers, &philos[i]);
	}
	if (pthread_create(&args->th[args->phi_nb], NULL, &check_deaths, &philos))
		ft_puterror(FAILED_CRT_THRD);
	x = 0;
	while (x < (args->phi_nb + 1) * (!args->exec) + args->exec
		* (args->exec != 0))
		pthread_join(args->th[x++], NULL);
	return (args->exec);
}
