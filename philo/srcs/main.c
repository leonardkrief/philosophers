/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/20 17:18:11 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args	args;

	if (ac <= 4)
		ft_putstr_fd("Too few arguments\n", 2);
	else if (ac >= 7)
		ft_putstr_fd("Too much arguments\n", 2);
	else
	{
		init_args(&args, ac, av);
		init_philos(&args);
		launch_philos(&args);
		join_philos(&args);
	}
}
