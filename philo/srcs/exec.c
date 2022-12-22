/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/22 19:53:41 by lkrief           ###   ########.fr       */
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
	if (!a->dead && a->fork[ph->n])
	{
		a->fork[ph->n] = 0;
		ph->l_fork = 1;
	}
	if (pthread_mutex_unlock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	if (pthread_mutex_lock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	if (!a->dead && a->fork[(ph->n + 1) % a->phi_nb] && a->phi_nb >= 2 )
	{
		a->fork[(ph->n + 1) % a->phi_nb] = 0;
		ph->r_fork = 1;
		gettimeofday(&ph->tp, NULL);
		printf("[%lld] %d has taken a fork\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1);
	}
	if (pthread_mutex_unlock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	return (ph->l_fork & ph->r_fork);
}

int	eats(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (is_dead(ph))
		return (ph->args->dead);
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
		return (ph->args->dead);
	if (ph->l_fork & ph->r_fork)
	{
		if (pthread_mutex_lock(&a->mutex[ph->n]))
			handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
		a->fork[ph->n] = 1;
		if (pthread_mutex_unlock(&a->mutex[ph->n]))
			handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
		if (pthread_mutex_lock(&a->mutex[(ph->n + 1) % a->phi_nb]))
			handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
		//printf("{%d} left_fork %d right_fork %d\n", ph->n + 1, ph->n, (ph->n + 1) % a->phi_nb);
		a->fork[(ph->n + 1) % a->phi_nb] = 1;
		if (pthread_mutex_unlock(&a->mutex[(ph->n + 1) % a->phi_nb]))
			handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
		ph->sleeps = 1;
		ph->l_fork = 0;
		ph->r_fork = 0;
		gettimeofday(&ph->tp, NULL);
		printf("[%lld] %d is sleeping\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1);
		usleep(ph->args->slp_tm);
	}
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
		// printf("{%d} eat nb %d, should eat %d\n", ph->n + 1, ph->ate, a->eat_nb);
		while((!ph->l_fork || !ph->r_fork) && !a->dead)
		// {
		// 	printforks(ph);
			gets_forks(ph);
		// }
		// printf("{%d.2} %d deads\n", ph->n + 1, a->dead);
		if (!a->dead)
			eats(ph);
		// printf("{%d.3} %d deads\n", ph->n + 1, a->dead);
		if(!a->dead)
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