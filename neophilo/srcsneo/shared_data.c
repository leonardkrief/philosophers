/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:26:44 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/16 19:12:03 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	init_shared_data(t_shared_data *sh, int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (-1);
	memset(sh, 0, sizeof(*sh));
	sh->total_philos = ft_atoi_ph(av[1]);
	sh->die_timer = ft_atoi_ph(av[2]) * 1000;
	sh->eat_timer = ft_atoi_ph(av[3]);
	sh->slp_timer = ft_atoi_ph(av[4]);
	if (ac == 6)
		sh->max_eat = ft_atoi_ph(av[5]);
	if (sh->total == -1 || sh->total > MAX_PHILOS || sh->max_eat == -1
		|| sh->die_timer == -1 || sh->eat_timer == -1 || sh->slp_timer == -1)
		return (-1);
	init_shared_data_mutexes
	return (0);
}

int	init_shared_data_mutexes(t_shared_data *sh)
{
	size_t	i;

	i = 0;
	while (i < sh->total_philos)
	{
		if (pthread_mutex_init_safe(sh->mutex_forks[i]))
			return (-1);
		i++;
	}
	if (pthread_mutex_init_safe(sh->print))
		return (-1);
	if (pthread_mutex_init_safe(sh->keeper))
		return (-1);
	if (pthread_mutex_init_safe(sh->death))
		return (-1);
	return (0);
}

int	free_shared_data(t_shared_data *sh)
{
	size_t	i;

	i = 0;
	while (i < sh->total_philos)
	{
		if (sh->mutex_forks[i])
			pthread_mutex_destroy_safe(sh->mutex_forks[i]);
		i++;
	}
	if (sh->print)
		pthread_mutex_destroy_safe(sh->print);
	if (sh->keeper)
		pthread_mutex_destroy_safe(sh->keeper);
	if (sh->death)
		pthread_mutex_destroy_safe(sh->death);
	return (0);
}
