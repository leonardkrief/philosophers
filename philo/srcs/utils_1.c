/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/27 13:46:05 by lkrief           ###   ########.fr       */
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

int	printlock(t_philo *ph, char *str, int i)
{
	if (died(ph))
		return (1);
	if (pthread_mutex_lock(&ph->args->print))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_LOCK);
	printf("[%ld] %d %s",
		ft_utdiff(get_time(), ph->args->start), ph->n + 1, str);
	if (i)
		printf("[%ld] %d %s",
			ft_utdiff(get_time(), ph->args->start), ph->n + 1, str);
	if (pthread_mutex_unlock(&ph->args->print))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_UNLOCK);
	return (0);
}
