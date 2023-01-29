/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 07:18:16 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/29 08:12:04 by lkrief           ###   ########.fr       */
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
		if (time >= dinner->infos->die_timer && !dinner->philo->end_death)
		{
			sem_wait_safe(dinner->infos->print);
			printf("%06ld %d %s", gettime_ms() - dinner->infos->init_time,
				dinner->philo->id, "died\n");
			sem_post_safe(dinner->infos->stop);
			break ;
		}
		else if (dinner->philo->end_death)
			break ;
		usleep(500);
	}
	printf("(%d)___END DEATH___\n", dinner->philo->id);
	return (NULL);
}

void	*stop_th(void *args)
{
	t_dinner	*dinner;

	dinner = (t_dinner *) args;
	// printf("(%d)____WAITSTOP____\n", dinner->philo->id);
	sem_wait_safe(dinner->infos->stop);
	// printf("(%d)____WAIT LOCAL STOP____\n", dinner->philo->id);
	// sem_wait_safe(dinner->philo->lstop);
	ft_usleep(1000);
	printf("(%d)____FREE____\n", dinner->philo->id);
	// sem_close_safe(dinner->philo->lstop);
	sem_close_safe(dinner->philo->time);
	sem_close_safe(dinner->infos->forks);
	sem_close_safe(dinner->infos->death);
	sem_close_safe(dinner->infos->error);
	sem_close_safe(dinner->infos->print);
	sem_post_safe(dinner->infos->stop);
	sem_close_safe(dinner->infos->stop);
	printf("(%d)____DONE FREE____\n", dinner->philo->id);
	dinner->philo->end_death = 1;
	if (pthread_join(dinner->philo->death_thread, NULL) == -1)
		ft_puterror(FAILED_WAITPID, (char *)__func__);
	return (0);
}