/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/21 18:58:11 by lkrief           ###   ########.fr       */
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

void	*ft_calloc(size_t count, size_t size)
{
	int		i;
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

// Time n must be given in milliseconds
int	set_time(struct timeval *t, int n)
{
	t->tv_sec = n / 1000000;
	t->tv_usec = n % 1000000;
}

int	ft_utimediff(struct timeval *t1, struct timeval *t2)
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
	if ((int)dif < INT_MIN)
		return (INT_MIN);
	else if ((int)dif > INT_MAX)
		return (INT_MAX);
	else
		return ((int)dif);
}
