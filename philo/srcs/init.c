/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/21 19:09:01 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args_stack(t_args *args, int ac, char **av)
{
	args->phi_nb = ft_atoi_ph(av[1]);
	args->die_tm = ft_atoi_ph(av[2]) * 1000;
	args->eat_tm = ft_atoi_ph(av[3]) * 1000;
	args->slp_tm = ft_atoi_ph(av[4]) * 1000;
	if (ac == 6)
		args->eat_nb = ft_atoi_ph(av[5]);
	args->th = NULL;
	args->fork = NULL;
	args->mutex = NULL;
}

int	init_args_heap(t_args *args)
{
	int	i;

	args->th = malloc (sizeof(*args->th) * (args->phi_nb));
	if (args->th == NULL)
		return (free_args(args, FAILED_MALLOC, 0));
	args->fork = ft_calloc ((args->phi_nb), sizeof(*args->fork));
	if (args->fork == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS, 0));
	memset(args->fork, 1, args->phi_nb);
	args->mutex = malloc (sizeof(*args->mutex) * args->phi_nb);
	if (args->mutex == NULL)
		return (free_args(args, FAILED_MALLOC | FREE_THREADS | FREE_FORKS, 0));
	i = -1;
	while (++i < args->phi_nb)
	{
		if (pthread_mutex_init(&args->mutex[i], NULL) != 0)
			return (free_args(args, FAILED_INIT_MUTEX | FREE_THREADS
				| FREE_FORKS | FREE_MUTEX, i));
	}
	return (0);
}

int	init_philo(t_args *args, t_philo *philo, int i)
{
	philo->args = args;
	philo->n = i;
	philo->ate = 0;
	philo->eating = 0;
	philo->last_meal = NULL;
	philo->tp = NULL;
	philo->last_meal = malloc (sizeof(*philo->last_meal));
	if (philo->last_meal == NULL)
		return (FAILED_MALLOC);
	philo->tp = malloc (sizeof(*philo->tp));
	if (philo->tp == NULL)
		return (FAILED_MALLOC);
	if (gettimeofday(philo->tp, NULL) != 0)
		return (FAILED_GET_TIME);
	return (0);
}
