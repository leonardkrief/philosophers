/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/02 16:32:06 by lkrief           ###   ########.fr       */
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

int	ft_atoi_ph(const char *str)
{
	unsigned int			i;
	long long int			nb;

	nb = 0;
	i = 0;
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

int	printlock(t_philo *ph, char *str, int i)
{
	if (died(ph))
		return (1);
	if (pthread_mutex_lock(&ph->args->print))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_LOCK);
	printf("%06ld %d %s", get_time() - convert_time(ph->args->init_time),
		ph->id + 1, str);
	if (i)
		printf("%06ld %d %s", get_time() - convert_time(ph->args->init_time),
			ph->id + 1, str);
	if (pthread_mutex_unlock(&ph->args->print))
		handle_thread_error(ph->args, ph, FAILED_MUTEX_UNLOCK);
	return (0);
}

void	ft_usleep(long time_ms)
{
	long	begin;

	begin = get_time();
	while (get_time() - begin < time_ms)
		usleep(500);
}
