/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/22 13:03:04 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_puterror(int flag)
{
	if ((flag & FAILURE & FAILED_CRT_THRD) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed creating thread\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_JOIN_THRD) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed joining thread\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_DETACH_THRD) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed detaching thread\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_MALLOC) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed malloc\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_INIT_MUTEX) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed init mutex\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_DESTROY_MUTEX) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed destroy mutex\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_MUTEX_LOCK) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed lock mutex\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_MUTEX_UNLOCK) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed unlock mutex\n", STDERR_FILENO);
}

int	free_args(t_args *args, int flag)
{
	unsigned int	i;

	if (flag & FREE_THREADS)
		free(args->th);
	if (flag & FREE_FORKS)
		free(args->fork);
	if (flag & DESTROY_MUTEX)
	{
		i = 0;
		while (i < args->phi_nb)
			pthread_mutex_destroy(&args->mutex[i++]);
		pthread_mutex_destroy(&args->safety);
	}
	if (flag & FREE_MUTEX)
		free(args->mutex);
	ft_puterror(flag);
	if (flag & EXIT_FLAG)
		exit(-(flag & FAILURE));
	return (flag & EXIT_FLAG);
}

void	handle_thread_error(t_args *args, t_philo *ph, int flag)
{
	if (!args->dead)
	{
		if (pthread_mutex_lock(&args->safety))
			args->dead = -FAILED_MUTEX_LOCK;
		args->dead = -flag;
		ft_putnbr_fd(ph->n, 2);
		ft_putstr_fd("  ERROR  ", 2);
		ft_puterror(flag);
		if (pthread_mutex_unlock(&args->safety))
			args->dead = -FAILED_MUTEX_UNLOCK;
	}
}