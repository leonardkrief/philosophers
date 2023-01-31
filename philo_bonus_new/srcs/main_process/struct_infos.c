/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_infos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 07:18:16 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/31 04:41:19 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_infos(t_infos *infos)
{
	if (infos->forks)
		sem_close_safe(infos->forks);
	if (infos->print)
		sem_close_safe(infos->print);
	if (infos->death)
		sem_close_safe(infos->death);
	if (infos->kill)
		sem_close_safe(infos->kill);
	if (infos->stop)
		sem_close_safe(infos->stop);
	exit (1);
}

void	*check_infos(t_infos *i)
{
	void	*check;

	check = i;
	if (i->philo_nb == -1 || i->philo_nb >= MAX_PHILOS || i->die_timer == -1
		|| i->eat_timer == -1 || i->slp_timer == -1 || i->max_meals == -1)
		check = ft_puterror(USERGUIDE, NULL);
	if (i->forks == NULL || i->print == NULL || i->death == NULL
			|| i->kill == NULL || i->stop == NULL || i->init_time == -1)
		check = NULL;
	return (check);
}

t_infos	*new_infos(t_infos *infos, int ac, char **av)
{
	if (ac <= 4 || ac >= 7)
		return (ft_puterror(USERGUIDE, NULL));
	memset(infos, 0, sizeof(*infos));
	infos->philo_nb = ft_atoi_philos(av[1]);
	infos->die_timer = ft_atoi_philos(av[2]);
	infos->eat_timer = ft_atoi_philos(av[3]);
	infos->slp_timer = ft_atoi_philos(av[4]);
	if (ac == 6)
		infos->max_meals = ft_atoi_philos(av[5]);
	infos->forks = sem_open_new_safe(SEM_FORKS, infos->philo_nb);
	infos->print = sem_open_new_safe(SEM_PRINT, 1);
	infos->death = sem_open_new_safe(SEM_DEATH, 0);
	infos->kill = sem_open_new_safe(SEM_ERROR, 0);
	infos->stop = sem_open_new_safe(SEM_STOP, 0);
	infos->init_time = gettime_ms();
	if (!check_infos(infos))
		return (free_infos(infos), NULL);
	return (infos);
}
