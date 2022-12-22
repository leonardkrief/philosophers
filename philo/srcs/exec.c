/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/22 18:39:34 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	gets_forks(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (is_dead(ph))
		return (ph->args->dead);
	if (pthread_mutex_lock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	printf("{%d} fork locked mutex %d\n", ph->n + 1, ph->n);
	if (pthread_mutex_lock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	printf("{%d} fork locked mutex %d\n", ph->n + 1, (ph->n + 1) % a->phi_nb);
	printf("{%d} left_fork %d right_fork %d\n", ph->n + 1, ph->n, (ph->n + 1) % a->phi_nb);
	if (a->fork[ph->n] && a->fork[(ph->n + 1) % a->phi_nb])
	{
		a->fork[ph->n] = 0;
		a->fork[(ph->n + 1) % a->phi_nb] = 0;
		ph->got_forks = 1;
		gettimeofday(&ph->tp, NULL);
		printf("[%lld] %d has taken a fork\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1);
		// printf("[%d] forks ph_n = %d   left_fork = %d   right_fork =  %d   eating = %d\n", ft_utdiff(&ph->tp, &a->start), ph->n, a->fork[ph->n], a->fork[(ph->n + 1) % a->phi_nb], ph->eating);
	}
	if (pthread_mutex_unlock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	printf("{%d} fork locked mutex %d\n", ph->n + 1, (ph->n + 1) % a->phi_nb);
	if (pthread_mutex_unlock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	printf("{%d} fork locked mutex %d\n", ph->n + 1, (ph->n + 1) % a->phi_nb);
	return (ph->eating);
}

int	eats(t_philo *ph)
{
	t_args			*a;

	if (is_dead(ph))
		return (ph->args->dead);
	a = ph->args;
	gettimeofday(&ph->tp, NULL);
	printf("[%lld] %d is eating\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1);
	ph->eating = 1;
	usleep(a->eat_tm);
	gettimeofday(&ph->last_meal, NULL);
	return (0);
}

int	sleeps(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (is_dead(ph))
		return (ph->args->dead);
	if (pthread_mutex_lock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	printf("{%d} sleep locked mutex %d\n", ph->n + 1, ph->n);
	if (pthread_mutex_lock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	printf("{%d} sleep locked mutex %d\n", ph->n + 1, (ph->n + 1) % a->phi_nb);
	printf("{%d} left_fork %d right_fork %d\n", ph->n + 1, ph->n, (ph->n + 1) % a->phi_nb);
	if (!a->fork[ph->n] && !a->fork[(ph->n + 1) % a->phi_nb])
	{
		a->fork[ph->n] = 1;
		a->fork[(ph->n + 1) % a->phi_nb] = 1;
		ph->sleeps = 1;
		gettimeofday(&ph->tp, NULL);
		printf("[%lld] %d is sleeping\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1);
		//printf("[%lld] sleep ph_n = %d   left_fork = %d   right_fork =  %d   eating = %d\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1, a->fork[ph->n], a->fork[(ph->n + 1) % a->phi_nb], ph->eating);
	}
	if (pthread_mutex_unlock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	printf("{%d} sleep unlocked mutex %d\n", ph->n + 1, (ph->n + 1) % a->phi_nb);
	if (pthread_mutex_unlock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	printf("{%d} sleep locked mutex %d\n", ph->n + 1, ph->n);
	usleep(a->slp_tm);
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
			ph->args->dead = FAILED_MUTEX_LOCK;
		if (!ph->args->dead)
		{
			gettimeofday(&ph->tp, NULL);
			printf("[%lld] %d died\n", ft_utdiff(&ph->tp, &ph->args->start), ph->n + 1);
			ph->dead = 1;
			ph->args->dead = ph->n + 1;
		}
		if (pthread_mutex_unlock(&ph->args->safety))
			ph->args->dead = FAILED_MUTEX_UNLOCK;
	}
	return (ph->args->dead);
}

void	*philosophers(void *philo)
{
	t_philo	*ph;
	t_args	*a;

	ph = (t_philo *)philo;
	a = ph->args;
	// if (pthread_mutex_lock(&a->safety))
	// 	a->exec = FAILED_MUTEX_LOCK;
	// if (pthread_mutex_unlock(&a->safety))
	// 	a->exec = FAILED_MUTEX_UNLOCK;
	while (!a->dead && (ph->ate++ < a->eat_nb || !a->eat_nb))
	{
		// printf("{%d.1} %d deads\n", ph->n + 1, a->dead);
		while(!ph->got_forks && !a->dead)
		// {
		// 	printforks(ph);
			gets_forks(ph);
		// }
		ph->got_forks = 0;
		// printf("{%d.2} %d deads\n", ph->n + 1, a->dead);
		while (!ph->eating && !a->dead)
			eats(ph);
		ph->eating = 0;
		// printf("{%d.3} %d deads\n", ph->n + 1, a->dead);
		while (!ph->sleeps && !a->dead)
			sleeps(ph);
		ph->sleeps = 0;
		gettimeofday(&ph->tp, NULL);
		if (!a->dead)
			printf("[%lld] %d is thinking\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1);
	}
	return (NULL);
}

/*
1. Mr. Beast
2. Emmanuel Macron forme finale Kyllian M'bappe
3.

*/