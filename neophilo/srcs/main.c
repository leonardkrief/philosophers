/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:22:39 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/18 04:14:22 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_shared_data	*shared_data;
	t_philo			philos[MAX_PHILOS];

	shared_data = malloc(sizeof(*shared_data));
	if (!shared_data)
		return (-1);
	if (init_shared_data(shared_data, ac, av) == -1)
	{
		printf(USERGUIDE);
		free(shared_data);
		return (-1);
	}
	launcher(shared_data, philos);
	free_shared_data(shared_data);
	return (0);
}
