/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/22 20:06:03 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (s)
	{
		i = -1;
		while (s[++i])
			write(fd, s + i, 1);
	}
}

void	ft_putnbr_fd(int nb, int fd)
{
	char			c;
	unsigned int	z;

	z = nb;
	if (nb < 0)
	{
		ft_putstr_fd("-", fd);
		z = -nb;
	}
	if (z >= 10)
		ft_putnbr_fd(z / 10, fd);
	c = '0' + z % 10;
	write(fd, &c, 1);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*tab;

	tab = malloc(count * size);
	if (!tab)
		return (NULL);
	memset(tab, 0, size * count);
	return (tab);
}

unsigned int	ft_atoi_ph(const char *str)
{
	unsigned int			i;
	long long unsigned int	nb;

	nb = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && nb <= INT_MAX / 1000)
		nb = 10 * nb + str[i++] - '0';
	if (nb > INT_MAX / 1000)
	{
		ft_putstr_fd("Input too big. Capped to INT_MAX / 1000\n", 2);
		return (INT_MAX / 1000);
	}
	return (nb);
}

long long int	ft_utdiff(struct timeval *t1, struct timeval *t2)
{
	long long int	dif;

	if (t1 == NULL && t2 == NULL)
		return (0);
	else if (t1 == NULL)
		dif = -(1000000 * t2->tv_sec + t2->tv_usec);
	else if (t2 == NULL)
		dif = 1000000 * t1->tv_sec + t1->tv_usec;
	else
		dif = 1000000 * (t1->tv_sec - t2->tv_sec) + (t1->tv_usec - t2->tv_usec);
	if (dif < LONG_MIN)
		return (LONG_MIN / 1000);
	else if (dif > LONG_MAX)
		return (LONG_MAX / 1000);
	else
		return (dif / 1000);
}
