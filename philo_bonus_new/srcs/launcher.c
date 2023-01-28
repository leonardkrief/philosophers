/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 07:18:16 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/28 15:03:18 by lkrief           ###   ########.fr       */
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
			return (new_dinner(id, infos));
	}
	wait_dinners(infos);
	return (0);
}
