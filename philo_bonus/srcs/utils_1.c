/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/03 01:12:10 by lkrief           ###   ########.fr       */
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
		{
			if (write(fd, s + i, 1) == -1)
				printf("Error writing\n");
		}
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
	if (write(fd, &c, 1) == -1)
		printf("Error writing\n");
}

int	ft_atoi_ph(const char *str)
{
	unsigned int			i;
	long long int			nb;

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

void	printlock(t_infos *infos, char *str)
{
	protected_sem_wait(infos->print, infos);
	printf("%06ld %d %s", get_time() - convert_time(infos->init_time),
		infos->id + 1, str);
	protected_sem_post(infos->print, infos);
}

void	ft_usleep(long time_ms)
{
	long	begin;

	begin = get_time();
	while (get_time() - begin < time_ms)
		usleep(500);
}
