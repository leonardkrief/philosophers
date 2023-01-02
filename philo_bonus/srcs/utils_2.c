/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/31 02:25:42 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

long	get_time_death(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1e6 + tp.tv_usec);
}

long	convert_time(struct timeval tp)
{
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

long	convert_time_us(struct timeval tp)
{
	return (tp.tv_sec * 1e6 + tp.tv_usec);
}

int	end_dinner(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->args->keeper))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_LOCK);
	ph->args->done++;
	if (pthread_mutex_unlock(&ph->args->keeper))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_UNLOCK);
	return (1);
}
