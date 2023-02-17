/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:46:17 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/17 18:12:51 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_forks(t_philo *ph)
{
	t_shared_data	*shared;
	int	i;

	i = -1;
	shared = &ph->shared;
	printf("%06.f %d Forks: {", gettime_ms() - shared->start_time, ph->id);
	while (++i < shared->total_philos)
	{
		pthread_mutex_lock_safe(&shared->mutex_forks[i]);
		printf("%d ", shared->forks[i]);
		pthread_mutex_unlock_safe(&shared->mutex_forks[i]);
	}
	printf("}\n");
}

void	*meal(void *philo)
{
	t_philo		*ph;

	ph = (t_philo *) philo;
	// if (ph->id % 2)
	// 	ft_ms_sleep(ph->shared.eat_timer * 0.7);
	while (1)
	{
		// if (ph->shared.total_philos % 2 && ph->meals > 0)
		// 	ft_ms_sleep(ph->shared.eat_timer * 0.5);
		if (gets_forks(ph) == -1)
			break ;
		if (eats(ph) == -1)
			break ;
		if (sleeps(ph) == -1)
			break ;
		printlock(ph, THINK_MESSAGE);
	}
	return (NULL);
}

int	gets_forks(t_philo *ph)
{
	while (ph->l_fork == false || ph->r_fork == false)
	{
		print_forks(ph);
		if (tries_fork(ph, 0))
			return (-1);
		if (tries_fork(ph, 1))
			return (-1);
		if (ph->l_fork == 0 || ph->r_fork == 0)
		{
			// let_go_forks(ph);
			usleep(200);
			printf("%06.f %d couldnt take forks", gettime_ms() - ph->shared.start_time, ph->id);
		}
		else
		{
			printlock(ph, FORK_MESSAGE);
			printlock(ph, FORK_MESSAGE);
		}
	}
	return (0);
}

int	tries_fork(t_philo *ph, int fork)
{
	int	fork_id;

	if (someone_died(ph) == -1)
		return (-1);
	if (fork == 0)
		fork_id = ph->id - 1;
	else if (fork == 1)
		fork_id = ph->id % ph->shared.total_philos;
	else
		return (-1);
	pthread_mutex_lock_safe(&ph->shared.mutex_forks[fork_id]);
	if (ph->shared.forks[fork_id] == 0)
	{
		ph->shared.forks[fork_id] = 1;
		if (fork == 0)
			ph->l_fork = true;
		else
			ph->r_fork = true;
	}
	pthread_mutex_unlock_safe(&ph->shared.mutex_forks[fork_id]);
	return (0);
}

void	let_go_forks(t_philo *ph)
{
	pthread_mutex_lock_safe(&ph->shared.mutex_forks[ph->id - 1]);
	if (ph->l_fork == true)
	{
		ph->shared.forks[ph->id - 1] = 0;
		ph->l_fork = false;
	}
	pthread_mutex_unlock_safe(&ph->shared.mutex_forks[ph->id - 1]);
	pthread_mutex_lock_safe(&ph->shared.mutex_forks[ph->id % ph->shared.total_philos]);
	if (ph->r_fork == true)
	{
		ph->shared.forks[ph->id % ph->shared.total_philos] = 0;
		ph->r_fork = false;
	}
	pthread_mutex_unlock_safe(&ph->shared.mutex_forks[ph->id % ph->shared.total_philos]);
}

int	eats(t_philo *ph)
{
	if (printlock(ph, EAT_MESSAGE))
		return (-1);
	ft_ms_sleep(ph->shared.eat_timer);
	pthread_mutex_lock_safe(&ph->shared.death);
	ph->last_meal = gettime_ms();
	pthread_mutex_unlock_safe(&ph->shared.death);
	ph->meals++;
	return (0);
}

int	sleeps(t_philo *ph)
{
	pthread_mutex_lock_safe(&ph->shared.mutex_forks[ph->id - 1]);
	ph->shared.forks[ph->id - 1] = 0;
	ph->l_fork = false;
	pthread_mutex_unlock_safe(&ph->shared.mutex_forks[ph->id - 1]);
	pthread_mutex_lock_safe(&ph->shared.mutex_forks[ph->id % ph->shared.total_philos]);
	ph->shared.forks[ph->id % ph->shared.total_philos] = 0;
	ph->r_fork = false;
	pthread_mutex_unlock_safe(&ph->shared.mutex_forks[ph->id % ph->shared.total_philos]);
	if (ph->meals == ph->shared.max_meals)
		return (-1);
	if (printlock(ph, SLEEP_MESSAGE))
		return (-1);
	ft_ms_sleep(ph->shared.slp_timer);
	return (0);
}