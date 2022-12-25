/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/25 04:39:53 by lkrief           ###   ########.fr       */
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
	args->dead = 0;
	args->exec = 0;
	args->start.tv_sec = 0;
	args->start.tv_usec = 0;
	args->th = NULL;
	args->fork = NULL;
	args->mutex = NULL;
}

int	init_args_heap(t_args *args)
{
	args->th = malloc (sizeof(*args->th) * (args->phi_nb + 1));
	if (args->th == NULL)
		return (free_args(args, FAILED_MALLOC));
	args->fork = malloc (sizeof(*args->fork) * args->phi_nb);
	if (args->fork == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS));
	memset(args->fork, 1, args->phi_nb);
	args->mutex = malloc (sizeof(*args->mutex) * args->phi_nb);
	if (args->mutex == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS | FREE_FORKS));
	args->dead = malloc (sizeof(*args->dead) * args->phi_nb);
	if (args->dead == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS | FREE_FORKS
			| FREE_MUTEX_FORKS));
	return (0);
}

int	init_philo(t_args *args, t_philo *philo, int i)
{
	philo->args = args;
	philo->n = i;
	philo->ate = 0;
	philo->r_fork = 0;
	philo->l_fork = 0;
	philo->dead = 0;
	if (gettimeofday(&philo->last_meal, NULL))
		return (FAILED_GET_TIME);
	if (pthread_mutex_init(&args->mutex[i], NULL))
		return (FAILED_INIT_MUTEX);
	if (pthread_mutex_init(&args->dead[i], NULL))
	{
		pthread_mutex_destroy(&args->mutex[i]);
		return (FAILED_INIT_MUTEX);
	}
	return (0);
}

int	exec_threads(t_args *args, t_philo *philos)
{
	unsigned int	i;
	unsigned int	x;

	if (gettimeofday(&args->start, NULL))
		args->exec = -1;
	i = -1;
	while (++i < args->phi_nb && !args->exec)
	{
		if (init_philo(args, &philos[i], i))
			args->exec = i;
		if (!args->exec
			&& pthread_create(&args->th[i], NULL, &philosophers, &philos[i]))
		{
			if (i > 0)
				died(&philos[0], FAILED_CRT_THRD);
		}
	}
	if (pthread_create(&args->th[args->phi_nb], NULL, &check_deaths, &philos))
		ft_puterror(FAILED_CRT_THRD);
	x = 0;
	while (x < (args->phi_nb + 1) * (!args->exec) + args->exec * (args->exec != 0))
	{
		if (pthread_join(args->th[x++], NULL))
			died(&philos[0], FAILED_JOIN_THRD);
	}
	return (args->exec);
}
