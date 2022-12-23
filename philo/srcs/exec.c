/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/23 12:39:42 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	gets_forks(t_philo *ph)
{
	if (is_dead(ph))
		return ;
	if (pthread_mutex_lock(&ph->args->mutex[ph->n]))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_LOCK);
	if (!ph->args->dead && ph->args->fork[ph->n])
	{
		ph->args->fork[ph->n] = 0;
		ph->l_fork = 1;
	}
	if (pthread_mutex_unlock(&ph->args->mutex[ph->n]))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_UNLOCK);
	if (pthread_mutex_lock(&ph->args->mutex[(ph->n + 1) % ph->args->phi_nb]))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_LOCK);
	if (!ph->args->dead && ph->args->fork[(ph->n + 1) % ph->args->phi_nb]
		&& ph->args->phi_nb >= 2)
	{
		ph->args->fork[(ph->n + 1) % ph->args->phi_nb] = 0;
		ph->r_fork = 1;
	}
	if (pthread_mutex_unlock(&ph->args->mutex[(ph->n + 1) % ph->args->phi_nb]))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_UNLOCK);
	check_both_forks(ph);
}

void	check_both_forks(t_philo *p)
{
	if (is_dead(p))
		return ;
	gettimeofday(&p->tp, NULL);
	if (p->l_fork && p->r_fork)
		printf("[%lld] %d has taken a fork\n",
			ft_utdiff(&p->tp, &p->args->start), p->n + 1);
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
}

void	eats(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (is_dead(ph))
		return ;
	gettimeofday(&ph->tp, NULL);
	printf("[%lld] %d is eating\n", ft_utdiff(&ph->tp, &a->start), ph->n + 1);
	usleep(a->eat_tm);
	gettimeofday(&ph->last_meal, NULL);
}

void	sleeps(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (is_dead(ph))
		return ;
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
	if (is_dead(ph))
		return ;
	gettimeofday(&ph->tp, NULL);
	printf("[%lld] %d is sleeping\n",
		ft_utdiff(&ph->tp, &a->start), ph->n + 1);
	usleep(ph->args->slp_tm);
}

int	is_dead(t_philo *ph)
{
	gettimeofday(&ph->tp, NULL);
	if (ft_utdiff(&ph->tp, &ph->last_meal) > ph->args->die_tm
		&& !ph->args->dead)
	{
		if (pthread_mutex_lock(&ph->args->safety))
			ph->args->dead = FAILED_MUTEX_LOCK;
		if (!ph->args->dead)
		{
			ph->dead = 1;
			ph->args->dead = ph->n + 1;
			gettimeofday(&ph->tp, NULL);
			printf("[%lld] %d died\n",
				ft_utdiff(&ph->tp, &ph->args->start), ph->n + 1);
		}
		if (pthread_mutex_unlock(&ph->args->safety))
			ph->args->dead = FAILED_MUTEX_UNLOCK;
	}
	return (ph->args->dead);
}
