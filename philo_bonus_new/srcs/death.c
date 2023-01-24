/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 07:18:16 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/24 07:20:59 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death_check(void *info)
{
	long			time;
	t_infos			*infos;

	infos = ((t_infos *)info);
	while (1)
	{
		sem_wait_safe(infos->time, infos);
		time = get_time_us() - convert_time_us(infos->last_meal);
		if (infos->should_return)
			end_dinner_death(infos, CLOSE_ALL);
		sem_post_safe(infos->time, infos);
		if (time >= infos->die_timer)
		{
			sem_wait_safe(infos->print, infos);
			printf("%06ld %d %s", get_time() - convert_time(
					infos->init_time), infos->id + 1, "died\n");
			end_dinner_death(infos, FAILED_CREAT_TH | CLOSE_ALL);
		}
		usleep(500);
	}
	return (NULL);
}