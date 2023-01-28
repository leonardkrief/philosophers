/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:56:47 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/28 14:53:56 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo *philo)
{
	if (philo->time)
		sem_close_safe(philo->time);
	if (philo->stop)
		sem_close_safe(philo->stop);
}

void	*check_philo(t_philo *philo)
{
	void	*check;

	check = philo;
	if (!philo->time || !philo->stop)
		check = NULL;
	return (check);
}

t_philo	*new_philo(t_dinner *dinner, int id)
{
	memset(dinner->philo, 0, sizeof(*dinner->philo));
	dinner->philo->id = id;
	dinner->philo->eaten_meals = 0;
	dinner->philo->time = sem_open_new_safe(SEM_TIME, 1);
	dinner->philo->stop = sem_open_new_safe(SEM_STOP, 1);
	dinner->philo->last_meal = dinner->infos->init_time;
	if (!check_philo(dinner->philo))
		return (free_philo(dinner->philo), NULL);
	if (pthread_create(&dinner->philo->death_thread, NULL, &death_th, (void *)dinner))
		return (free_philo(dinner->philo), NULL);
	return (dinner->philo);
}