/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/24 06:27:18 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	gets_forks(t_infos *infos)
{
	sem_wait_safe(infos->forks, infos);
	printlock(infos, "has taken a fork\n");
	sem_wait_safe(infos->forks, infos);
	printlock(infos, "has taken a fork\n");
}

int	eats(t_infos *infos)
{
	printlock(infos, "is eating\n");
	ft_usleep(infos->eat_timer);
	sem_wait_safe(infos->time, infos);
	gettimeofday(&infos->last_meal, NULL);
	sem_post_safe(infos->time, infos);
	sem_post_safe(infos->forks, infos);
	sem_post_safe(infos->forks, infos);
	infos->ate++;
	if (infos->ate == infos->max_eat)
	{
		sem_wait_safe(infos->time, infos);
		infos->should_return = 1;
		sem_post_safe(infos->time, infos);
		pthread_detach(infos->death_thread);
		ft_usleep(300);
		end_dinner_meals(infos);
	}
	return (0);
}

void	sleeps(t_infos *infos)
{
	printlock(infos, "is sleeping\n");
	ft_usleep(infos->slp_timer);
}

void	thinks(t_infos *infos)
{
	printlock(infos, "is thinking\n");
}
