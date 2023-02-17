/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meal.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:46:17 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/17 15:04:37 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*meal(void *philo)
{
	t_philo		*ph;

	ph = (t_philo *) philo;
	printf("philo %d is alive", ph->id);
	while (1)
	{
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
	while (ph->l_fork == 0 || ph->r_fork == 0)
	{
		if (tries_fork(ph, 0))
			return (-1);
		if (tries_fork(ph, 1))
			return (-1);
		if (ph->l_fork == 0 || ph->r_fork == 0)
			let_go_forks(ph);
		usleep(500);
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
			ph->l_fork = 1;
		else
			ph->r_fork = 1;
	}
	pthread_mutex_unlock_safe(&ph->shared.mutex_forks[fork_id]);
	return (0);
}

void	let_go_forks(t_philo *ph)
{
	pthread_mutex_lock_safe(&ph->shared.mutex_forks[ph->id - 1]);
	if (ph->l_fork == 1)
	{
		ph->shared.forks[ph->id - 1] = 0;
		ph->l_fork = 0;
	}
	pthread_mutex_unlock_safe(&ph->shared.mutex_forks[ph->id - 1]);
	pthread_mutex_lock_safe(&ph->shared.mutex_forks[ph->id % ph->shared.total_philos]);
	if (ph->r_fork == 1)
	{
		ph->shared.forks[ph->id % ph->shared.total_philos] = 0;
		ph->r_fork = 0;
	}
	pthread_mutex_unlock_safe(&ph->shared.mutex_forks[ph->id % ph->shared.total_philos]);
}

int	eats(t_philo *ph)
{
	if (printlock(ph, EAT_MESSAGE))
		return (-1);
	ft_ms_sleep(ph->shared.eat_timer);
	pthread_mutex_lock(&ph->shared.death);
	ph->last_meal = gettime_ms();
	pthread_mutex_unlock(&ph->shared.death);
	ph->meals++;
	return (0);
}

int	sleeps(t_philo *ph)
{
	pthread_mutex_lock_safe(&ph->shared.mutex_forks[ph->id - 1]);
	ph->shared.forks[ph->id - 1] = 0;
	pthread_mutex_unlock_safe(&ph->shared.mutex_forks[ph->id - 1]);
	pthread_mutex_lock_safe(&ph->shared.mutex_forks[ph->id % ph->shared.total_philos]);
	ph->shared.forks[ph->id % ph->shared.total_philos] = 0;
	pthread_mutex_unlock_safe(&ph->shared.mutex_forks[ph->id % ph->shared.total_philos]);
	ph->l_fork = 1;
	ph->r_fork = 1;
	if (ph->meals == ph->shared.max_meals)
		return (-1);
	if (printlock(ph, SLEEP_MESSAGE))
		return (-1);
	ft_ms_sleep(ph->shared.slp_timer);
	return (0);
}