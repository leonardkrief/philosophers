/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/30 16:45:33 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime_ms(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL))
	{
		ft_puterror(FAILED_GET_TIME, (char *) __func__);
		return (-1);
	}
	return (tp.tv_sec * 1e3 + tp.tv_usec / 1e3);
}

long	gettime_us(void)
{
	struct timeval	tp;

	if (gettimeofday(&tp, NULL))
	{
		ft_puterror(FAILED_GET_TIME, (char *) __func__);
		return (-1);
	}
	return (tp.tv_sec * 1e6 + tp.tv_usec);
}

long	converttime_ms(struct timeval tp)
{
	return (tp.tv_sec * 1e3 + tp.tv_usec / 1e3);
}

long	converttime_us(struct timeval tp)
{
	return (tp.tv_sec * 1e6 + tp.tv_usec);
}
