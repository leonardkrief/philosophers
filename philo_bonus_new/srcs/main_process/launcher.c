/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 07:18:16 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/30 16:04:25 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_dinners(t_infos *infos)
{
	int	id;

	id = 0;
	while (++id <= infos->philo_nb)
	{
		if (waitpid(infos->pids[id - 1], NULL, 0) == -1)
			ft_puterror(FAILED_WAITPID, (char *)__func__);
	}
}

int	launcher(t_infos *infos)
{
	int	id;

	id = 0;
	while (++id <= infos->philo_nb)
	{
		infos->pids[id - 1] = fork();
		if (infos->pids[id - 1] < 0)
			return (ft_puterror(FAILED_FORK, (char *)__func__), id);
		if (infos->pids[id - 1] == 0)
			return (new_philo(id, infos));
	}
	wait_dinners(infos);
	return (0);
}

int	finish_dinner(t_infos *infos)
{
	int	check;

	check = 0;
	if (sem_close_safe(infos->forks))
		check = 1;
	if (sem_close_safe(infos->death))
		check = 1;
	if (sem_close_safe(infos->error))
		check = 1;
	if (sem_close_safe(infos->print))
		check = 1;
	if (sem_close_safe(infos->stop))
		check = 1;
	return (check);
}