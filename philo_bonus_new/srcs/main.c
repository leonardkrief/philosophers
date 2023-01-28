/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:15:20 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/28 14:15:32 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_infos	infos;

	if (new_infos(&infos, ac, av) == NULL)
		return (1);
	if (launcher(&infos))
		return (2);
	// if (termination(infos) == NULL)
	// 	return (3);
	return (0);
}