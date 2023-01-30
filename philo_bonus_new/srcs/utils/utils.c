/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/30 16:45:13 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (s && fd >= 0)
	{
		while (*s)
		{
			if (write(fd, s++, 1) == -1)
			{
				ft_puterror(FAILED_WRITE, (char *)__func__);
				return (0);
			}
		}
	}
	return (1);
}

int	ft_putnbr_fd(int nb, int fd)
{
	char			c;
	unsigned int	z;

	z = nb;
	if (nb < 0)
	{
		ft_putstr_fd("-", fd);
		z = -nb;
	}
	if (z >= 10 && !ft_putnbr_fd(z / 10, fd))
		return (0);
	c = '0' + z % 10;
	if (write(fd, &c, 1) == -1)
	{
		write(fd, "Failed write\n", 13);
		return (0);
	}
	return (1);
}

int	ft_atoi_philos(const char *str)
{
	unsigned int	i;
	long long int	nb;

	nb = 0;
	i = 0;
	if (!str)
		return (-1);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && nb <= INT_MAX)
		nb = 10 * nb + str[i++] - '0';
	if (nb > INT_MAX)
		return (-1);
	if (!((str[i] >= 9 && str[i] <= 13) || str[i] == ' ' || str[i] == 0))
		return (-1);
	return (nb);
}

void	printlock(t_dinner *dinner, char *str)
{
	sem_wait_safe(dinner->infos->print);
	printf("%06ld %d %s", gettime_ms() - dinner->infos->init_time,
		dinner->philo->id, str);
	sem_post_safe(dinner->infos->print);
}

void	ft_usleep(long time_ms)
{
	long	begin;
	struct timeval tp;

	memset(&tp, 0, sizeof (tp));
	begin = gettime_ms();
	while (gettime_ms() - begin < time_ms)
		usleep(1000);
}
