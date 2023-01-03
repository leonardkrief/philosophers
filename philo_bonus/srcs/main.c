/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/02 23:47:43 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_infos	infos;

	if (ac <= 4 || ac >= 7)
	{
		ft_putstr_fd("usage:\n\t./philo {nb_philos} {die_tm}", 2);
		ft_putstr_fd(" {eat_tm} {sleep_tm} (max_eat)\n", 2);
		ft_putstr_fd("\tinputs in ms is capped to 60,000 ms\n", 2);
	}
	if (init_infos(&infos, ac, av))
	{
		ft_putstr_fd("usage:\n\t./philo {nb_philos} {die_tm}", 2);
		ft_putstr_fd(" {eat_tm} {sleep_tm} (max_eat)\n", 2);
		ft_putstr_fd("\tinputs in ms is capped to 60,000 ms\n", 2);
	}
	else
		launch_dinners(&infos);
}
