/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/22 07:07:39 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	gets_forks(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (is_dead(ph))
		return (handle_death(a, ph));
	if (pthread_mutex_lock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	//printf("[%d] %d okay 1\n", ft_utdiff(&ph->tp, &a->start), ph->n);
	if (pthread_mutex_lock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	if (a->fork[ph->n] && a->fork[(ph->n + 1) % a->phi_nb])
	{
		gettimeofday(&ph->tp, NULL);
		printf("[%lld] %d has taken a fork\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1);
		a->fork[ph->n] = 0;
		a->fork[(ph->n + 1) % a->phi_nb] = 0;
		ph->eating = 1;
		// printf("[%d] forks ph_n = %d   left_fork = %d   right_fork =  %d   eating = %d\n", ft_utdiff(&ph->tp, &a->start), ph->n, a->fork[ph->n], a->fork[(ph->n + 1) % a->phi_nb], ph->eating);
	}
	if (pthread_mutex_unlock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	if (pthread_mutex_unlock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	return (ph->eating);
}

int	eats(t_philo *ph)
{
	t_args			*a;

	if (is_dead(ph))
		return (handle_death(ph->args, ph));
	a = ph->args;
	gettimeofday(&ph->tp, NULL);
	printf("[%lld] %d is eating\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1);
	usleep(a->eat_tm);
	gettimeofday(&ph->last_meal, NULL);
	return (0);
}

int	sleeps(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (is_dead(ph))
		return (handle_death(a, ph));
	if (pthread_mutex_lock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	if (pthread_mutex_lock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	// printf("[%lld] trysleep ph_n = %d   left_fork = %d   right_fork =  %d   eating = %d\n", ft_utdiff(&ph->tp, &a->start), ph->n, a->fork[ph->n], a->fork[(ph->n + 1) % a->phi_nb], ph->eating);
	if (!a->fork[ph->n] && !a->fork[(ph->n + 1) % a->phi_nb])
	{
		a->fork[ph->n] = 1;
		a->fork[(ph->n + 1) % a->phi_nb] = 1;
		ph->eating = 0;
		gettimeofday(&ph->tp, NULL);
		printf("[%lld] %d is sleeping\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1);
		printf("[%lld] sleep ph_n = %d   left_fork = %d   right_fork =  %d   eating = %d\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1, a->fork[ph->n], a->fork[(ph->n + 1) % a->phi_nb], ph->eating);
		usleep(a->slp_tm);
	}
	if (pthread_mutex_unlock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	if (pthread_mutex_unlock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	return (0);
}

int	is_dead(t_philo *ph)
{
	gettimeofday(&ph->tp, NULL);
	// printf("%d youkou %ld %d %ld %d\n", ph->n, ph->tp.tv_sec, ph->tp.tv_usec, ph->args->start.tv_sec, ph->args->start.tv_usec);
	if (ft_utdiff(&ph->tp, &ph->last_meal) > ph->args->die_tm
		&& !ph->args->dead)
	{
		if (pthread_mutex_lock(&ph->args->safety))
			ph->args->exec = FAILED_MUTEX_LOCK;
		ph->dead = 1;
		ph->args->dead = 1;
		if (pthread_mutex_unlock(&ph->args->safety))
			ph->args->exec = FAILED_MUTEX_UNLOCK;
		return (1);
	}
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
	while (!a->exec && (ph->ate++ < a->eat_nb || !a->eat_nb))
	{
		while(!ph->eating && !a->dead)
		{
			// if (!ph->eating)
			// 	printforks(ph);
			gets_forks(ph);
		}
		printforks(ph);
		ph->eating = 0;
		if (!a->dead)
			eats(ph);
		if (!a->dead)
			sleeps(ph);
		gettimeofday(&ph->tp, NULL);
		if (!a->dead)
			printf("[%lld] %d is thinking\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1);
	}
	return (NULL);
}