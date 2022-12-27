/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/27 13:39:27 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	gets_forks(t_philo *ph)
{
	if (pthread_mutex_lock(&ph->args->mutex[ph->n]))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_LOCK);
	if (ph->args->fork[ph->n])
	{
		ph->args->fork[ph->n] = 0;
		ph->l_fork = 1;
	}
	if (pthread_mutex_unlock(&ph->args->mutex[ph->n]))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_UNLOCK);
	if (pthread_mutex_lock(&ph->args->mutex[(ph->n + 1) % ph->args->phi_nb]))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_LOCK);
	if (ph->args->fork[(ph->n + 1) % ph->args->phi_nb] && ph->args->phi_nb >= 2)
	{
		ph->args->fork[(ph->n + 1) % ph->args->phi_nb] = 0;
		ph->r_fork = 1;
	}
	if (pthread_mutex_unlock(&ph->args->mutex[(ph->n + 1) % ph->args->phi_nb]))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_UNLOCK);
	return (check_both_forks(ph));
}

int	check_both_forks(t_philo *p)
{
	if (p->l_fork && p->r_fork)
		return (printlock(p, "has taken a fork\n", 1));
	else if (p->l_fork)
	{
		if (pthread_mutex_lock(&p->args->mutex[p->n]))
			handle_thread_error(p->args, p, FAILED_MUTEX_LOCK);
		p->args->fork[p->n] = 1;
		if (pthread_mutex_unlock(&p->args->mutex[p->n]))
			handle_thread_error(p->args, p, FAILED_MUTEX_UNLOCK);
		p->l_fork = 0;
	}
	else if (p->r_fork)
	{
		if (pthread_mutex_lock(&p->args->mutex[(p->n + 1) % p->args->phi_nb]))
			handle_thread_error(p->args, p, FAILED_MUTEX_LOCK);
		p->args->fork[(p->n + 1) % p->args->phi_nb] = 1;
		if (pthread_mutex_unlock(&p->args->mutex[(p->n + 1) % p->args->phi_nb]))
			handle_thread_error(p->args, p, FAILED_MUTEX_UNLOCK);
		p->r_fork = 0;
	}
	return (0);
}

int	eats(t_philo *ph)
{
	t_args	*a;

	a = ph->args;
	if (printlock(ph, "is eating\n", 0))
		return (1);
	ft_usleep(a->eat_tm);
	pthread_mutex_lock(ph->death);
	gettimeofday(&ph->args->death[ph->n].last_meal, NULL);
	pthread_mutex_unlock(ph->death);
	ph->ate++;
	return (0);
}

int	sleeps(t_philo *ph)
{
	t_args	*a;

	a = ph->args;
	if (pthread_mutex_lock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	a->fork[ph->n] = 1;
	if (pthread_mutex_unlock(&a->mutex[ph->n]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	if (pthread_mutex_lock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_LOCK);
	a->fork[(ph->n + 1) % a->phi_nb] = 1;
	if (pthread_mutex_unlock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		handle_thread_error(a, ph, FAILED_MUTEX_UNLOCK);
	ph->l_fork = 0;
	ph->r_fork = 0;
	if (ph->ate == ph->args->eat_nb)
		return (end_dinner(ph));
	if (printlock(ph, "is sleeping\n", 0))
		return (1);
	ft_usleep(ph->args->slp_tm);
	return (0);
}

int	died(t_philo *ph)
{
	int	dead;

	dead = 0;
	pthread_mutex_lock(&ph->args->keeper);
	dead = ph->args->one_died;
	pthread_mutex_unlock(&ph->args->keeper);
	return (dead);
}
