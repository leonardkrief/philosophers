/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 01:38:58 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/18 04:21:53 by lkrief           ###   ########.fr       */
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
		pthread_create_safe(&shared->threads[i], &meal_routine,
			&philos[i], shared);
		if (error_occured(philos))
			break ;
	}
	if (!error_occured(philos))
	{
		pthread_create_safe(&shared->threads[i], &death_routine,
			philos, shared);
		i++;
	}
	j = -1;
	while (++j < i)
		pthread_join_safe(shared->threads[j], shared);
	return (0);
}

void	init_philo(t_shared_data *shared, t_philo *philo, int i)
{
	memset(philo, 0, sizeof(*philo));
	philo->id = i + 1;
	philo->shared = shared;
	philo->last_meal = shared->start_time;
}
