/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/21 19:09:07 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_philos(t_args *args)
{
	int				flag;
	t_philo			*philo;
	unsigned int	i;

	i = 0;
	while (i < args->phi_nb)
	{
		philo = malloc(sizeof(*philo));
		if (philo == NULL)
			return (FAILED_MALLOC);
		flag = init_philo(args, philo, i);
		if (flag != 0)
			break ;
		flag = FAILED_CRT_THRD;
		if (pthread_create(&args->th[i], NULL, &philosophers, philo) != 0)
			break ;
		i++;
	}
	// gerer le free si la boucle au dessus fail: attendre que tous les threads
	// deja lances terminent pour free args et le philo cassé
}

void	gets_forks(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (pthread_mutex_lock(&a->mutex[ph->n]))
		printf("HANDLE ERROR"); // Handle error
	if (pthread_mutex_lock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		printf("HANDLE ERROR"); // Handle error
	if (a->fork[ph->n] && a->fork[(ph->n + 1) % a->phi_nb] && ph->eating == 0)
	{
		gettimeofday(ph->tp, NULL);
		printf("%d %d has taken a fork", ft_utimediff(ph->tp, NULL), ph->n);
		a->fork[ph->n] = 0;
		a->fork[(ph->n + 1) % a->phi_nb] = 0;
		ph->eating = 1;
	}
	if (pthread_mutex_unlock(&a->mutex[ph->n]))
		printf("HANDLE ERROR"); // Handle error
	if (pthread_mutex_unlock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		printf("HANDLE ERROR"); // Handle error
}

void	eats(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (ph->eating == 1)
	{
		gettimeofday(ph->tp, NULL);
		printf("%d %d is eating", ft_utimediff(ph->tp, NULL), ph->n);
		usleep(a->eat_tm);
		ph->eating = 0;
	}
}

void	sleeps(t_philo *ph)
{
	t_args			*a;

	a = ph->args;
	if (pthread_mutex_lock(&a->mutex[ph->n]))
		printf("HANDLE ERROR"); // Handle error
	if (pthread_mutex_lock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		printf("HANDLE ERROR"); // Handle error
	if (!a->fork[ph->n] && !a->fork[(ph->n + 1) % a->phi_nb] && ph->eating == 1)
	{
		a->fork[ph->n] = 1;
		a->fork[(ph->n + 1) % a->phi_nb] = 1;
	}
	if (pthread_mutex_unlock(&a->mutex[ph->n]))
		printf("HANDLE ERROR"); // Handle error
	if (pthread_mutex_unlock(&a->mutex[(ph->n + 1) % a->phi_nb]))
		printf("HANDLE ERROR"); // Handle error
	gettimeofday(ph->tp, NULL);
	printf("%d %d is sleeping", ft_utimediff(ph->tp, NULL), ph->n);
	usleep(a->slp_tm);
}

int	is_dead(t_philo *ph)
{
	gettimeofday(ph->tp, NULL);
	if ((unsigned int)ft_utimediff(ph->tp, ph->last_meal) > ph->args->die_tm)
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
	while (ft_utimediff(ph->last_meal, NULL) > 0 && ph->ate++ < a->eat_nb)
	{
		if (is_dead(ph))
			//Handle death
		gets_forks(ph);
		if (is_dead(ph))
			//Handle death
		eats(ph);
		sleeps(ph);
		if (is_dead(ph))
			//Handle death
		gettimeofday(ph->tp, NULL);
		printf("%d %d is thinking", ft_utimediff(ph->tp, NULL), ph->n);
	}
	return (NULL);
}
