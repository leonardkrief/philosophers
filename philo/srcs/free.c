/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/22 04:25:01 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_puterror(int flag)
{
	if (flag & FAILED_CRT_THRD & STDERR_FLAG)
		ft_putstr_fd("Failed creating thread\n", STDERR_FILENO);
	else if (flag & FAILED_JOIN_THRD & STDERR_FLAG)
		ft_putstr_fd("Failed joining thread\n", STDERR_FILENO);
	else if (flag & FAILED_DETACH_THRD & STDERR_FLAG)
		ft_putstr_fd("Failed detaching thread\n", STDERR_FILENO);
	else if (flag & FAILED_MALLOC & STDERR_FLAG)
		ft_putstr_fd("Failed malloc\n", STDERR_FILENO);
	else if (flag & FAILED_INIT_MUTEX & STDERR_FLAG)
		ft_putstr_fd("Failed init mutex\n", STDERR_FILENO);
	else if (flag & FAILED_DESTROY_MUTEX & STDERR_FLAG)
		ft_putstr_fd("Failed destroy mutex\n", STDERR_FILENO);
	else if (flag & FAILED_MUTEX_LOCK & STDERR_FLAG)
		ft_putstr_fd("Failed lock mutex\n", STDERR_FILENO);
	else if (flag & FAILED_MUTEX_UNLOCK & STDERR_FLAG)
		ft_putstr_fd("Failed unlock mutex\n", STDERR_FILENO);
}

int	free_args(t_args *args, int flag)
{
	int	i;

	if (flag & FREE_THREADS)
		free(args->th);
	if (flag & FREE_FORKS)
		free(args->fork);
	if (flag & DESTROY_MUTEX)
	{
		i = -1;
		while (++i < args->phi_nb)
			pthread_mutex_destroy(&args->mutex[i]);
	}
	if (flag & FREE_MUTEX)
		free(args->mutex);
	ft_puterror(flag);
	if (flag & EXIT_FLAG)
		exit(-(flag & FAILURE));
	return (flag & EXIT_FLAG);
}

void handle_death(t_args *args, t_philo *ph)
{
	if (!args->exec)
	{
		if (pthread_mutex_lock(&args->safety))
			args->exec = FAILED_MUTEX_LOCK;
		args->exec = -ph->n;
		printf("[%d] %d died", ft_utdiff(&ph->birth, &args->start), ph->n);
		if (pthread_mutex_unlock(&args->safety))
			args->exec = FAILED_MUTEX_UNLOCK;
	}
}

void	handle_thread_error(t_args *args, t_philo *ph, int flag)
{
	if (!args->exec)
	{
		if (pthread_mutex_lock(&args->safety))
			args->exec = FAILED_MUTEX_LOCK;
		args->exec = flag;
		ft_putnbr_fd(ph->n, 2);
		ft_putstr_fd("   ", 2);
		ft_puterror(flag);
		if (pthread_mutex_unlock(&args->safety))
			args->exec = FAILED_MUTEX_UNLOCK;
	}
}