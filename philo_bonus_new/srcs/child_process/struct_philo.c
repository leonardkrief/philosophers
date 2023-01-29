/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:56:47 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/29 07:25:05 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_philo(t_philo *philo)
{
	if (philo->time)
		sem_close_safe(philo->time);
	(void) philo;
}

void	*check_philo(t_philo *philo)
{
	void	*check;

	check = philo;
	if (!philo->time)
		check = NULL;
	return (check);
}

void	get_semname(char *sem, char *name, int id)
{
	int	i;

	i = -1;
	while (++i < 5)
		sem[i] = name[i];
	sem[i++] = '0' + (id / 100) % 10;
	sem[i++] = '0' + (id / 10) % 10;
	sem[i++] = '0' + id % 10;
	sem[i++] = '\0';
}

t_philo	*new_philo(t_dinner *dinner, int id)
{
	memset(dinner->philo, 0, sizeof(*dinner->philo));
	dinner->philo->id = id;
	dinner->philo->eaten_meals = 0;
	get_semname(dinner->philo->semtime_name, SEM_TIME, id);
	dinner->philo->time = sem_open_new_safe(dinner->philo->semtime_name, 1);
	// get_semname(dinner->philo->semlstop_name, SEM_LOCALSTOP, id);
	// dinner->philo->lstop = sem_open_new_safe(dinner->philo->semlstop_name, 1);
	dinner->philo->last_meal = dinner->infos->init_time;
	if (!check_philo(dinner->philo))
		return (free_philo(dinner->philo), NULL);
	if (pthread_create(&dinner->philo->death_thread, NULL, &death_th, (void *)dinner))
		return (free_philo(dinner->philo), NULL);
	if (pthread_create(&dinner->philo->stop_thread, NULL, &stop_th, (void *)dinner))
		return (free_philo(dinner->philo), NULL);
	return (dinner->philo);
}