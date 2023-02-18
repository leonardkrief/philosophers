/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:54:56 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/18 04:16:22 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pthread_create_safe(pthread_t *thread, void *(*start_routine)(void *),
		void *arg, t_shared_data *shared)
{
	if (pthread_create(thread, NULL, start_routine, arg))
	{
		ft_puterror(FAILED_THREAD_CREATE, (char *) __func__);
		pthread_mutex_lock_safe(&shared->error, shared);
		shared->error_bool = true;
		pthread_mutex_unlock_safe(&shared->error, shared);
		return (FAILED_THREAD_CREATE);
	}
	return (0);
}

int	pthread_join_safe(pthread_t thread, t_shared_data *shared)
{
	if (pthread_join(thread, NULL))
	{
		pthread_mutex_lock_safe(&shared->error, shared);
		shared->error_bool = true;
		pthread_mutex_unlock_safe(&shared->error, shared);
		ft_puterror(FAILED_THREAD_JOIN, (char *) __func__);
		return (FAILED_THREAD_JOIN);
	}
	return (0);
}

int	pthread_detach_safe(pthread_t thread, t_shared_data *shared)
{
	if (pthread_detach(thread))
	{
		pthread_mutex_lock_safe(&shared->error, shared);
		shared->error_bool = true;
		pthread_mutex_unlock_safe(&shared->error, shared);
		ft_puterror(FAILED_THREAD_DETACH, (char *) __func__);
		return (FAILED_THREAD_DETACH);
	}
	return (0);
}
