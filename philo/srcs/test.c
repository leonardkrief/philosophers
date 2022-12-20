/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/20 06:25:21 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_args args;

	if (ac <= 4)
		ft_putstr_fd("Too few arguments\n", 2);
	else if (ac >= 7)
		ft_putstr_fd("Too much arguments\n", 2);
	else
	{
		init_args(&args, ac, av);
		init_philo(&args);
		int i = -1;
		while (++i < args.phi_nb)
		{
			if (pthread_create(&args.ph[i], NULL, &philosopher, NULL) != 0)
				free_philo(&args, FAILED_CRT_THRD);
		}
		int i = -1;
		while (++i < args.phi_nb)
		{
			if (pthread_join(args.ph[i], NULL) != 0)
				free_philo(&args, FAILED_JOIN_THRD);
		}
	}
}