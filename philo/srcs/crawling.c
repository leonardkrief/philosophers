/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crawling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/20 14:09:28 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args_stack(t_args *args, int ac, char **av)
{
	args->phi_nb = ft_atoi_ph(av[1]);
	args->die_tm = ft_atoi_ph(av[2]);
	args->eat_tm = ft_atoi_ph(av[3]);
	args->slp_tm = ft_atoi_ph(av[4]);
	if (ac == 6)
		args->eat_nb = ft_atoi_ph(av[5]);
	args->tp = NULL;
	args->ph = NULL;
	args->life = NULL;
	args->fork = NULL;
}

void	*init_args_heap(t_args *args)
{
	int	i;

	args->tp = malloc (sizeof(*args->tp));
	if (args->tp == NULL)
		free_philos(args, FAILED_MALLOC);
	if (gettimeofday(args->tp, NULL) != 0)
		free_philos(args, FAILED_GET_TIME | FREE_GET_TIME);
	// need to remove this tp later and FREE_GET_TIME flags
	args->ph = malloc (sizeof(*args->ph) * (args->phi_nb));
	if (args->ph == NULL)
		free_philos(args, FAILED_MALLOC | FREE_GET_TIME);
	args->life = ft_calloc ((args->phi_nb), sizeof(*args->life));
	if (args->life == NULL)
		free_philos(args, FAILED_MALLOC | FREE_GET_TIME | FREE_PHILOS);
	i = -1;
	while (++i < args->phi_nb)
		args->life[i] = args->die_tm;
	args->fork = ft_calloc ((args->phi_nb), sizeof(*args->fork));
	if (args->fork == NULL)
		free_philos(args, FAILED_MALLOC | FREE_GET_TIME |
			FREE_PHILOS | FREE_FORKS);
	memset(args->fork, 1, args->phi_nb);
	if (pthread_mutex_init(&args->mutex, NULL) != 0)
		free_philos(args, FAILED_INIT_MUTEX | FREE_GET_TIME | FREE_PHILOS
			| FREE_FORKS | FREE_LIVES);
}

void	ft_puterror(int flag)
{
	if (flag & EXIT_NB & FAILED_CRT_THRD)
		ft_putstr_fd("Failed creating thread\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_JOIN_THRD)
		ft_putstr_fd("Failed joining thread\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_DETACH_THRD)
		ft_putstr_fd("Failed detaching thread\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_MALLOC)
		ft_putstr_fd("Failed malloc\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_INIT_MUTEX)
		ft_putstr_fd("Failed init mutex\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_DESTROY_MUTEX)
		ft_putstr_fd("Failed destroy mutex\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_LOCK_MUTEX)
		ft_putstr_fd("Failed lock mutex\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_UNLOCK_MUTEX)
		ft_putstr_fd("Failed unlock mutex\n", STDERR_FILENO);
}

void	*free_philos(t_args *args, int flag)
{
	if (flag & FREE_PHILOS)
		free(args->ph);
	if (flag & FREE_LIVES)
		free(args->life);
	if (flag & FREE_FORKS)
		free(args->fork);
	if (flag & FREE_MUTEX)
		pthread_mutex_destroy(&args->mutex);
	ft_puterror(flag);
	if (flag & EXIT_FLAG)
		exit(-(flag & EXIT_NB));
}
