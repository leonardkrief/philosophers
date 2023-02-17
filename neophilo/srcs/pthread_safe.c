/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_safe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 18:54:56 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/17 17:37:20 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pthread_create_safe(pthread_t *thread, void *(*start_routine)(void *), void *arg)
{
	if (pthread_create(thread, NULL, start_routine, arg))
	{
		ft_puterror(FAILED_THREAD_CREATE, (char *) __func__);
		return (FAILED_THREAD_CREATE);
	}
	return (0);
}

int	pthread_join_safe(pthread_t thread)
{
	if (pthread_join(thread, NULL))
	{
		ft_puterror(FAILED_THREAD_JOIN, (char *) __func__);
		return (FAILED_THREAD_JOIN);
	}
	return (0);
}

int	pthread_detach_safe(pthread_t thread)
{
	if (pthread_detach(thread))
	{
		ft_puterror(FAILED_THREAD_DETACH, (char *) __func__);
		return (FAILED_THREAD_DETACH);
	}
	return (0);
}
