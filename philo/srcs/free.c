/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/20 17:33:51 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	*free_args(t_args *args, int flag)
{
	if (flag & FREE_THREADS)
		free(args->th);
	if (flag & FREE_FORKS)
		free(args->fork);
	if (flag & FREE_MUTEX)
		pthread_mutex_destroy(&args->mutex);
	ft_puterror(flag);
	if (flag & EXIT_FLAG)
		exit(-(flag & EXIT_NB));
}

void	*free_philos(t_args *args, int flag)
{
	
}