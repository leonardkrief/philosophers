/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/20 14:21:46 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philo(t_args *args, t_philo *philo, int i)
{
	philo = malloc(sizeof(*philo));
	if (philo == NULL)
		return (FAILED_MALLOC);
	philo->args = args;
	philo->n = i;
	philo->ate = 0;
	philo->tp = malloc (sizeof(*philo->tp));
	if (philo->tp == NULL)
		return (FAILED_MALLOC);
	if (gettimeofday(philo->tp, NULL) != 0)
		return (FAILED_GET_TIME);
	return (0);
}

void	launch_philos(t_args *args)
{
	int		flag;
	t_philo	*philo;

	int i = -1;
	while (++i < args->phi_nb)
	{
		flag = init_philo(args, philo, i);
		if (flag != 0)
			break ;
		flag = FAILED_CRT_THRD;
		if (pthread_create(&args->ph[i], NULL, &philosophers, philo) != 0)
			break ;
	}
	// gerer le free si la boucle au dessus fail: attendre que tous les threads deja 
	// lances terminent pour free args et le philo cassé
}

void	*philosophers(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	while (a->life[ph->n] > 0 && ph->ate++ < a->eat_nb)
	{
		pthread_mutex_lock(&a->mutex);
		if (a->fork[ph->n] && a->fork[(ph->n + 1) % a->phi_nb])
		{
			printf("timestamp_in_ms %d has taken a fork", time, ph->n);
			usleep();
		}
		pthread_mutex_unlock(&a->mutex);
	}
}