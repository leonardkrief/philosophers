/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:22:39 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/16 19:19:30 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_shared_data	shared_data;
	t_philo			philos;

	if (init_shared_data(&shared_data, ac, av) == -1)
	{
		ft_puterror(USERGUIDE, NULL);
		return (-1);
	}
	launcher
	return (flag);
}
