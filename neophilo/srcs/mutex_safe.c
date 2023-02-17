/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_safe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:54:56 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/16 18:59:37 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pthread_mutex_init_safe(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL))
	{
		ft_puterror(FAILED_MUTEX_INIT, (char *) __func__);
		return (FAILED_MUTEX_INIT);
	}
	return (0);
}

int	pthread_mutex_destroy_safe(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex))
	{
		ft_puterror(FAILED_MUTEX_DESTROY, (char *) __func__);
		return (FAILED_MUTEX_DESTROY);
	}
	return (0);
}

int	pthread_mutex_lock_safe(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex))
	{
		ft_puterror(FAILED_MUTEX_LOCK, (char *) __func__);
		return (FAILED_MUTEX_LOCK);
	}
	return (0);
}

int	pthread_mutex_unlock_safe(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex))
	{
		ft_puterror(FAILED_MUTEX_UNLOCK, (char *) __func__);
		return (FAILED_MUTEX_UNLOCK);
	}
	return (0);
}