/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/20 18:03:48 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_args_stack(t_args *args, int ac, char **av)
{
	args->phi_nb = ft_atoi_ph(av[1]);
	args->die_tm = ft_atoi_ph(av[2]);
	args->eat_tm = ft_atoi_ph(av[3]);
	args->slp_tm = ft_atoi_ph(av[4]);
	if (ac == 6)
		args->eat_nb = ft_atoi_ph(av[5]);
	args->th = NULL;
	args->fork = NULL;
	args->mutex = NULL
}

void	*init_args_heap(t_args *args)
{
	int	i;

	args->th = malloc (sizeof(*args->th) * (args->phi_nb));
	if (args->th == NULL)
		free_philos(args, FAILED_MALLOC);
	args->fork = ft_calloc ((args->phi_nb), sizeof(*args->fork));
	if (args->fork == NULL)
		free_philos(args, FAILED_MALLOC | FREE_THREADS);
	memset(args->fork, 1, args->phi_nb);
	args->mutex = malloc (sizeof(*args->mutex) * args->phi_nb);
	if (args->mutex == NULL)
		free_philos(args, FAILED_MALLOC | FREE_THREADS | FREE_FORKS);
	i = -1;
	while (++i < args->phi_nb)
	{
		if (pthread_mutex_init(&args->mutex[i], NULL) != 0)
			free_philos(args, FAILED_INIT_MUTEX | FREE_THREADS
				| FREE_FORKS | FREE_MUTEX);
		// needs to pass one more arg to free philos to know how many
		// mutexes to destroy
	}
}

int	init_philo(t_args *args, t_philo *philo, int i)
{
	philo = malloc(sizeof(*philo));
	if (philo == NULL)
		return (FAILED_MALLOC);
	philo->args = args;
	philo->n = i;
	philo->ate = 0;
	philo->eating = 0;
	philo->to_live = NULL;
	philo->tp = NULL;
	philo->to_live = malloc (sizeof(*philo->to_live));
	if (philo->to_live == NULL)
		return (FAILED_MALLOC);
	philo->to_live->tv_sec = 1000 * args->die_tm / 1000000;
	philo->to_live->tv_usec = (1000 * args->die_tm) % 1000000;
	philo->tp = malloc (sizeof(*philo->tp));
	if (philo->tp == NULL)
		return (FAILED_MALLOC);
	if (gettimeofday(philo->tp, NULL) != 0)
		return (FAILED_GET_TIME);
	return (0);
}
