/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/02 18:50:35 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL))
	{
		ft_puterror(FAILED_GET_TIME);
		exit (-1);
	}
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

long	get_time_us(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL))
	{
		ft_puterror(FAILED_GET_TIME);
		exit (-1);
	}
	return (tp.tv_sec * 1e6 + tp.tv_usec);
}

long	convert_time(struct timeval tp)
{
	return (tp.tv_sec * 1000 + tp.tv_usec / 1000);
}

long	convert_time_us(struct timeval tp)
{
	return (tp.tv_sec * 1e6 + tp.tv_usec);
}
