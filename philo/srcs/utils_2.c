/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/27 13:46:12 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long int	ft_utdiff(long t1, long t2)
{
	return (t1 - t2);
}

long	get_time(void)
{
	struct timeval	tp;

	gettimeofday(&tp, NULL);
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

long	convert_time(struct timeval tp)
{
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

int	end_dinner(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->args->keeper))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_LOCK);
	ph->args->plate++;
	if (pthread_mutex_unlock(&ph->args->keeper))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_UNLOCK);
	return (1);
}

void	ft_usleep(long time_ms)
{
	long	begin;

	begin = get_time();
	while (get_time() - begin < time_ms)
		usleep(10);
}
