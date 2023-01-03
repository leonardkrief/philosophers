/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/03 02:45:09 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	gets_forks(t_infos *infos)
{
	protected_sem_wait(infos->forks, infos);
	printlock(infos, "has taken a fork\n");
	protected_sem_wait(infos->forks, infos);
	printlock(infos, "has taken a fork\n");
	// int value;
	// sem_getvalue(infos->forks, &value);
	// printf ("(%d) %d FORKS LEFT\n", infos->id + 1, value);
}

int	eats(t_infos *infos)
{
	// int value;
	// sem_getvalue(infos->time, &value);
	// printf ("TIME %d\n", value);
	printlock(infos, "is eating\n");
	ft_usleep(infos->eat_timer);
	protected_sem_wait(infos->time, infos);
	gettimeofday(&infos->last_meal, NULL);
	protected_sem_post(infos->time, infos);
	protected_sem_post(infos->forks, infos);
	protected_sem_post(infos->forks, infos);
	infos->ate++;
	if (infos->ate == infos->max_eat)
		end_dinner_meals(infos);
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
