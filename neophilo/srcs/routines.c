/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 04:20:06 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/18 04:39:39 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*meal_routine(void *philo)
{
	t_philo		*ph;

	ph = (t_philo *) philo;
	if (ph->id % 2 == 0)
		ft_ms_sleep(ph->shared->eat_timer * 0.7);
	while (1)
	{
		if (ph->shared->total_philos % 2 && ph->meals > 0)
			ft_ms_sleep(ph->shared->eat_timer * 0.2);
		if (error_occured(ph))
			break ;
		if (gets_forks(ph) == -1)
			break ;
		if (eats(ph) == -1)
			break ;
		if (sleeps(ph) == -1)
			break ;
		printlock(ph, THINK_MESSAGE);
	}
	return (NULL);
}

void	*death_routine(void *philos)
{
	int		i;
	t_philo	*philo;

	philo = (t_philo *) philos;
	while (1)
	{
		i = -1;
		pthread_mutex_lock_safe(&philo->shared->death, philo->shared);
		while (++i < philo->shared->total_philos)
		{
			if (philo->shared->done_meals == philo->shared->total_philos)
				return (pthread_mutex_unlock_safe(&philo->shared->death,
						philo->shared), NULL);
			if (gettime_ms() - philo[i].last_meal >= philo->shared->die_timer)
			{
				pthread_mutex_unlock_safe(&philo->shared->death, philo->shared);
				printlock(&philo[i], DEAD_MESSAGE);
				philo->shared->death_bool = true;
				return (NULL);
			}
		}
		pthread_mutex_unlock_safe(&philo->shared->death, philo->shared);
		usleep(500);
	}
	return (NULL);
}
