/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:46:17 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/18 04:42:45 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	gets_forks(t_philo *ph)
{
	if (ph->shared->total_philos == 1)
		printlock(ph, FORK_MESSAGE);
	while (ph->l_fork == false || ph->r_fork == false)
	{
		if (tries_fork(ph, 0) || tries_fork(ph, 1))
			return (-1);
		if (ph->l_fork == 0 || ph->r_fork == 0)
		{
			let_go_forks(ph);
			usleep(200);
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

	fork_id = 0;
	if (someone_died(ph) == -1)
		return (-1);
	if (fork == 0)
		fork_id = ph->id - 1;
	else if (fork == 1)
		fork_id = ph->id % ph->shared->total_philos;
	pthread_mutex_lock_safe(&ph->shared->mutex_forks[fork_id], ph->shared);
	if (ph->shared->forks[fork_id] == 0)
	{
		ph->shared->forks[fork_id] = 1;
		if (fork == 0)
			ph->l_fork = true;
		else
			ph->r_fork = true;
	}
	pthread_mutex_unlock_safe(&ph->shared->mutex_forks[fork_id], ph->shared);
	return (0);
}

void	let_go_forks(t_philo *ph)
{
	pthread_mutex_lock_safe(&ph->shared->mutex_forks[ph->id - 1], ph->shared);
	if (ph->l_fork == true)
	{
		ph->shared->forks[ph->id - 1] = 0;
		ph->l_fork = false;
	}
	pthread_mutex_unlock_safe(&ph->shared->mutex_forks[ph->id - 1], ph->shared);
	pthread_mutex_lock_safe(&ph->shared->mutex_forks[
		ph->id % ph->shared->total_philos], ph->shared);
	if (ph->r_fork == true)
	{
		ph->shared->forks[ph->id % ph->shared->total_philos] = 0;
		ph->r_fork = false;
	}
	pthread_mutex_unlock_safe(&ph->shared->mutex_forks[
		ph->id % ph->shared->total_philos], ph->shared);
}

int	eats(t_philo *ph)
{
	if (printlock(ph, EAT_MESSAGE))
		return (-1);
	ft_ms_sleep(ph->shared->eat_timer);
	pthread_mutex_lock_safe(&ph->shared->death, ph->shared);
	ph->last_meal = gettime_ms();
	pthread_mutex_unlock_safe(&ph->shared->death, ph->shared);
	return (0);
}

int	sleeps(t_philo *ph)
{
	pthread_mutex_lock_safe(&ph->shared->mutex_forks[ph->id - 1], ph->shared);
	ph->shared->forks[ph->id - 1] = 0;
	ph->l_fork = false;
	pthread_mutex_unlock_safe(&ph->shared->mutex_forks[ph->id - 1], ph->shared);
	pthread_mutex_lock_safe(&ph->shared->mutex_forks[
		ph->id % ph->shared->total_philos], ph->shared);
	ph->shared->forks[ph->id % ph->shared->total_philos] = 0;
	ph->r_fork = false;
	pthread_mutex_unlock_safe(&ph->shared->mutex_forks[
		ph->id % ph->shared->total_philos], ph->shared);
	pthread_mutex_lock_safe(&ph->shared->death, ph->shared);
	if (++ph->meals == ph->shared->max_meals)
	{
		ph->shared->done_meals++;
		pthread_mutex_unlock_safe(&ph->shared->death, ph->shared);
		return (-1);
	}
	pthread_mutex_unlock_safe(&ph->shared->death, ph->shared);
	if (printlock(ph, SLEEP_MESSAGE))
		return (-1);
	ft_ms_sleep(ph->shared->slp_timer);
	return (0);
}
