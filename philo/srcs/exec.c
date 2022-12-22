/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/22 04:34:05 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	gets_forks(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (pthread_mutex_lock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	if (pthread_mutex_lock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	if (a->fork[ph->n] && a->fork[(ph->n + 1) % a->phi_nb] && ph->eating == 0)
	{
		gettimeofday(&ph->birth, NULL);
		printf("[%d] %d has taken a fork", ft_utdiff(&ph->birth, &a->start), ph->n);
		a->fork[ph->n] = 0;
		a->fork[(ph->n + 1) % a->phi_nb] = 0;
		ph->eating = 1;
	}
	if (pthread_mutex_unlock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	if (pthread_mutex_unlock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
}

void	eats(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (ph->eating == 1)
	{
		gettimeofday(&ph->birth, NULL);
		printf("[%d] %d is eating", ft_utdiff(&ph->birth, &a->start), ph->n);
		usleep(a->eat_tm);
		ph->eating = 0;
	}
}

void	sleeps(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (pthread_mutex_lock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	if (pthread_mutex_lock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	if (!a->fork[ph->n] && !a->fork[(ph->n + 1) % a->phi_nb] && ph->eating == 1)
	{
		a->fork[ph->n] = 1;
		a->fork[(ph->n + 1) % a->phi_nb] = 1;
	}
	if (pthread_mutex_unlock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	if (pthread_mutex_unlock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	gettimeofday(&ph->birth, NULL);
	printf("[%d] %d is sleeping", ft_utdiff(&ph->birth, &a->start), ph->n);
	usleep(a->slp_tm);
}

int	is_dead(t_philo *ph)
{
	gettimeofday(&ph->birth, NULL);
	if ((unsigned int)ft_utdiff(&ph->birth, &ph->last_meal) > ph->args->die_tm)
		return (1);
	else
		return (0);
}

void	*philosophers(void *philo)
{
	t_philo	*ph;
	t_args	*a;

	ph = (t_philo *)philo;
	a = ph->args;
	if (pthread_mutex_lock(&a->safety))
		a->exec = FAILED_MUTEX_LOCK;
	if (pthread_mutex_unlock(&a->safety))
		a->exec = FAILED_MUTEX_UNLOCK;
	// ce mutex permet d'attendre que tous les threads soient
	// crees avant de les lancer, peut etre pas necessaire ?
	while (!a->exec && ph->ate++ < a->eat_nb)
	{
		if (is_dead(ph))
			handle_death(a, ph);
		gets_forks(ph);
		if (is_dead(ph))
			handle_death(a, ph);
		eats(ph);
		sleeps(ph);
		if (is_dead(ph))
			handle_death(a, ph);
		gettimeofday(&ph->birth, NULL);
		printf("[%d] %d is thinking", ft_utdiff(&ph->birth, &a->start), ph->n);
	}
	return (NULL);
}