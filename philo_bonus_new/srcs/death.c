/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 07:18:16 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/28 14:09:41 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_th(void *args)
{
	t_dinner	*dinner;
	long		time;

	dinner = (t_dinner *) args;
	while (1)
	{
		// sem_wait_safe(infos->time, infos);
		time = gettime_ms() - dinner->philo->last_meal;
		// sem_post_safe(infos->time, infos);
		if (time >= dinner->infos->die_timer)
		{
			sem_wait_safe(dinner->infos->print);
			printf("%06ld %d %s", gettime_ms() - dinner->infos->init_time,
				dinner->philo->id, "died\n");
			break ;
		}
		usleep(500);
	}
	return (NULL);
}