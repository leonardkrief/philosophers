/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 07:18:16 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/31 04:38:21 by lkrief           ###   ########.fr       */
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
		sem_wait_safe(dinner->philo->time);
		time = gettime_ms() - dinner->philo->last_meal;
		sem_post_safe(dinner->philo->time);
		if (time >= dinner->infos->die_timer)
		{
			sem_wait_safe(dinner->infos->print);
			printf("%06ld %d %s", gettime_ms() - dinner->infos->init_time,
				dinner->philo->id, "died\n");
			sem_post_safe(dinner->infos->stop);
			break ;
		}
		ft_usleep(5);
	}
	sem_post_safe(dinner->infos->kill);
	printf("(%d)___END DEATH___\n", dinner->philo->id);
	return (NULL);
}

void	*stop_th(void *args)
{
	t_dinner	*dinner;

	dinner = (t_dinner *) args;
	sem_wait_safe(dinner->infos->stop);
	sem_post_safe(dinner->infos->stop);
	ft_usleep(100);
	sem_close_safe(dinner->philo->time);
	sem_close_safe(dinner->infos->death);
	sem_close_safe(dinner->infos->kill);
	sem_close_safe(dinner->infos->print);
	sem_close_safe(dinner->infos->stop);
	sem_close_safe(dinner->infos->forks);
	printf("(%d)___END STOP___\n", dinner->philo->id);
	exit (0);
}