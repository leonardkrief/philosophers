/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:38:58 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/17 18:12:38 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	launcher(t_shared_data *shared, t_philo philos[])
{
	int	i;
	int	j;

	shared->start_time = gettime_ms();
	i = -1;
	while (++i < shared->total_philos)
	{
		init_philo(shared, &philos[i], i);
		if (pthread_create_safe(&philos[i].thread, &meal, &philos[i]))
		{
			pthread_mutex_lock_safe(&shared->error);
			shared->error_bool = true;
			pthread_mutex_unlock_safe(&shared->error);
			break ;
		}
	}
	j = -1;
	while (++j < i)
		pthread_join_safe(philos[j].thread);
	return ((i == shared->total_philos) - 1);
}

void	init_philo(t_shared_data *shared, t_philo *philo, int i)
{
	memset(philo, 0, sizeof(*philo));
	philo->id = i + 1;
	philo->shared = *shared;
	philo->last_meal = shared->start_time;
}