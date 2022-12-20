/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crawling.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/20 06:39:46 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args(t_args *args, int ac, char **av)
{
	args->phi_nb = ft_atoi_ph(av[1]);
	args->die_tm = ft_atoi_ph(av[2]);
	args->eat_tm = ft_atoi_ph(av[3]);
	args->slp_tm = ft_atoi_ph(av[4]);
	if (ac == 6)
		args->eat_nb = ft_atoi_ph(av[5]);
	args->ph = NULL;
}

void	*init_philo(t_args *args)
{
	args->ph = malloc (sizeof(*args->ph) * (args->phi_nb));
	if (args->ph == NULL)
		free_philo(args, FAILED_MALLOC_PHILO);
	if (pthread_mutex_init(&args->mutex, NULL) != 0)
		free_philo(args, FAILED_INIT_MUTEX);
}

void	ft_puterror(int flag)
{
	if (flag & EXIT_NB & FAILED_CRT_THRD)
		ft_putstr_fd("Failed creating thread\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_JOIN_THRD)
		ft_putstr_fd("Failed joining thread\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_DETACH_THRD)
		ft_putstr_fd("Failed detaching thread\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_MALLOC_PHILO)
		ft_putstr_fd("Failed malloc philosopher\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_INIT_MUTEX)
		ft_putstr_fd("Failed init mutex\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_DESTROY_MUTEX)
		ft_putstr_fd("Failed destroy mutex\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_LOCK_MUTEX)
		ft_putstr_fd("Failed lock mutex\n", STDERR_FILENO);
	else if (flag & EXIT_NB & FAILED_UNLOCK_MUTEX)
		ft_putstr_fd("Failed unlock mutex\n", STDERR_FILENO);
}

void	*free_philo(t_args *args, int flag)
{
	if (args->ph)
		free(args->ph);
	
	ft_puterror(flag);
	if (flag & EXIT_FLAG)
		exit(-(flag & EXIT_NB));
}
