/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/17 15:01:30 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (write(fd, s + i, 1) == -1)
				return (-1);
			i++;
		}
	}
	return (i);
}

int	ft_atoi_ph(const char *str)
{
	unsigned int			i;
	long int				nb;

	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && nb <= MAX_TIMER)
		nb = 10 * nb + str[i++] - '0';
	if (nb > MAX_TIMER)
		return (-1);
	if (!((str[i] >= 9 && str[i] <= 13) || str[i] == ' ' || str[i] == 0))
		return (-1);
	return (nb);
}

int	someone_died(t_philo *ph)
{
	pthread_mutex_lock_safe(&ph->shared.death);
	if (ph->shared.death_bool)
	{
		pthread_mutex_unlock_safe(&ph->shared.death);
		return (-1);
	}
	pthread_mutex_unlock_safe(&ph->shared.death);
	return (0);
}

int	printlock(t_philo *ph, t_message message)
{
	static const char	*message_strings[LAST_MESSAGE] = {
	"has taken a fork\n",
	"is eating\n",
	"is sleeping\n",
	"is thinking\n",
	"died\n",
	};

	if (someone_died(ph))
		return (-1);
	pthread_mutex_lock_safe(&ph->shared.print);
	printf("%06f %d %s", gettime_ms() - ph->shared.start_time,
		ph->id, message_strings[message]);
	pthread_mutex_unlock_safe(&ph->shared.print);
	return (0);
}
