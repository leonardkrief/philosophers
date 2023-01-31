/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 07:18:16 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/31 04:55:08 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	gets_forks(t_dinner *dinner)
{
	sem_wait_safe(dinner->infos->forks);
	printlock(dinner, "has taken a fork\n");
	sem_wait_safe(dinner->infos->forks);
	printlock(dinner, "has taken a fork\n");
	return (0);
}

int	eats(t_dinner *dinner)
{
	printlock(dinner, "is eating\n");
	ft_usleep(dinner->infos->eat_timer);
	sem_wait_safe(dinner->philo->time);
	dinner->philo->last_meal = gettime_ms();
	sem_post_safe(dinner->philo->time);
	sem_post_safe(dinner->infos->forks);
	sem_post_safe(dinner->infos->forks);
	dinner->philo->eaten_meals++;
	if (dinner->philo->eaten_meals == dinner->infos->max_meals)
	{
		sem_post_safe(dinner->infos->stop);
		return (1);
	}
	return (0);
}

void	sleeps(t_dinner *dinner)
{
	printlock(dinner, "is sleeping\n");
	ft_usleep(dinner->infos->slp_timer);
}

void	thinks(t_dinner *dinner)
{
	printlock(dinner, "is thinking\n");
}

int	new_philo(int id, t_infos *infos)
{
	t_dinner	dinner;
	t_philo		philo;

	dinner.infos = infos;
	dinner.philo = &philo;
	if (!new_dinner(&dinner, id))
		exit (1);
	if (dinner.philo->id == dinner.infos->philo_nb)
	{
		int	i = 0;
		while (i++ < dinner.infos->philo_nb)
			sem_post_safe(dinner.infos->print);
	}
	sem_wait_safe(dinner.infos->print);
	long tt =  gettime_ms();
	printf("(%d) diff = %ld\n", dinner.philo->id, tt - dinner.infos->init_time);
	exit (0);
	if (!(id % 2))
		ft_usleep(3 * dinner.infos->eat_timer / 4);
	while (1)
	{
		if (gets_forks(&dinner))
			break ;
		if (eats(&dinner))
			break ;
		sleeps(&dinner);
		thinks(&dinner);
		usleep(100);
	}
	return (0);
}