/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/24 06:27:36 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_infos(t_infos *infos, int ac, char **av)
{
	memset(infos, 0, sizeof(*infos));
	infos->total = ft_atoi_ph(av[1]);
	infos->die_timer = ft_atoi_ph(av[2]) * 1000;
	infos->eat_timer = ft_atoi_ph(av[3]);
	infos->slp_timer = ft_atoi_ph(av[4]);
	if (ac == 6)
		infos->max_eat = ft_atoi_ph(av[5]);
	if (infos->total < 0 || infos->max_eat < 0 || infos->die_timer < 0
		|| infos->eat_timer < 0 || infos->slp_timer < 0 || infos->total > 250)
		return (1);
	infos->print = sem_open_new_safe(SEM_PRINT, 1, infos, FAILED_SEM_OPEN);
	infos->time = sem_open_new_safe(SEM_TIME, 1, infos, FAILED_SEM_OPEN
			| CLOSE_SEM_PRINT);
	infos->forks = sem_open_new_safe(SEM_FORKS, infos->total, infos,
			FAILED_SEM_OPEN | CLOSE_SEM_PRINT | CLOSE_SEM_TIME);
	infos->died = sem_open_new_safe(SEM_DIED, 0, infos, FAILED_SEM_OPEN
			| CLOSE_SEM_PRINT | CLOSE_SEM_TIME | CLOSE_SEM_FORKS);
	infos->meals = sem_open_new_safe(SEM_MEALS, 0, infos, FAILED_SEM_OPEN
			| CLOSE_SEM_PRINT | CLOSE_SEM_TIME | CLOSE_SEM_FORKS
			| CLOSE_SEM_DIED);
	return (0);
}

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

void	*meals_check(void *info)
{
	int		i;
	t_infos	*infos;

	infos = ((t_infos *)info);
	i = -1;
	while (++i < infos->total)
		sem_wait_safe(infos->meals, infos);
	ft_usleep(50);
	free_infos(infos, CLOSE_ALL | EXIT_FLAG);
	return (NULL);
}

void	launch_philo(t_infos *i)
{
	i->forks = sem_open_safe(SEM_FORKS, i, FAILED_SEM_OPEN | CLOSE_ALL);
	i->print = sem_open_safe(SEM_PRINT, i, FAILED_SEM_OPEN | CLOSE_ALL);
	i->time = sem_open_safe(SEM_TIME, i, FAILED_SEM_OPEN | CLOSE_ALL);
	i->meals = sem_open_safe(SEM_MEALS, i, FAILED_SEM_OPEN | CLOSE_ALL);
	if (pthread_create(&i->death_thread, NULL, &death_check, (void *)i))
		end_dinner_death(i, FAILED_CREAT_TH | CLOSE_ALL);
	if (i->id % 2)
		ft_usleep(i->eat_timer / 3);
	while (1)
	{
		if (i->total % 2)
			ft_usleep(i->eat_timer / 3);
		gets_forks(i);
		eats(i);
		sleeps(i);
		thinks(i);
	}
	if (pthread_join(i->death_thread, NULL))
		end_dinner_death(i, FAILED_CREAT_TH | CLOSE_ALL);
	free_infos(i, CLOSE_ALL | EXIT_FLAG);
}

void	*launch_dinners(t_infos *infos)
{
	int	i;

	if (gettimeofday(&infos->init_time, NULL))
		return (free_infos(infos, FAILED_GET_TIME | CLOSE_ALL));
	i = -1;
	while (++i < infos->total)
	{
		infos->id = i;
		infos->last_meal = infos->init_time;
		infos->pids[i] = fork();
		if (infos->pids[i] == -1)
			free_infos(infos, FAILED_FORK | CLOSE_ALL);
		if (infos->pids[i] == 0)
			launch_philo(infos);
	}
	infos->id = i;
	if (pthread_create(&infos->meals_thread, NULL, &meals_check, (void *)infos))
		end_dinners_from_main(infos, FAILED_CREAT_TH | CLOSE_ALL);
	sem_wait_safe(infos->died, infos);
	end_dinners_from_main(infos, CLOSE_ALL);
	return (free_infos(infos, CLOSE_ALL));
}
