/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 07:18:16 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/28 14:41:59 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	gets_forks(t_dinner *dinner)
{
	sem_wait_safe(dinner->infos->forks);
	printlock(dinner, "has taken a fork\n");
	sem_wait_safe(dinner->infos->forks);
	printlock(dinner, "has taken a fork\n");
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
		return (1);
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

int	new_dinner(int id, t_infos *infos)
{
	t_dinner	dinner;
	t_philo		philo;

	dinner.infos = infos;
	dinner.philo = &philo;
	if (!new_philo(&dinner, id))
		//exits nicely
		return (1);
	if (dinner.philo->id % 2)
		ft_usleep(dinner.infos->eat_timer / 3);
	while (1)
	{
		if (dinner.infos->philo_nb % 2)
			ft_usleep(dinner.infos->eat_timer / 3);
		gets_forks(&dinner);
		if (eats(&dinner))
			return (0);
		sleeps(&dinner);
		thinks(&dinner);
	}
	return (0);
}