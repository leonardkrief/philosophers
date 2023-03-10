/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/24 06:27:18 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_puterror(int flag)
{
	if (flag & FAILURE & FAILED_FORK)
		ft_putstr_fd("Failed fork\n", STDERR_FILENO);
	else if (flag & FAILURE & FAILED_WAITPID)
		ft_putstr_fd("Failed waitpid\n", STDERR_FILENO);
	else if (flag & FAILURE & FAILED_SEM_OPEN)
		ft_putstr_fd("Failed sem_open\n", STDERR_FILENO);
	else if (flag & FAILURE & FAILED_SEM_CLOSE)
		ft_putstr_fd("Failed sem_close\n", STDERR_FILENO);
	else if (flag & FAILURE & FAILED_SEM_POST)
		ft_putstr_fd("Failed sem_post\n", STDERR_FILENO);
	else if (flag & FAILURE & FAILED_SEM_WAIT)
		ft_putstr_fd("Failed sem_wait\n", STDERR_FILENO);
	else if (flag & FAILURE & FAILED_SEM_UNLINK)
		ft_putstr_fd("Failed sem_unlink\n", STDERR_FILENO);
	else if (flag & FAILURE & FAILED_CREAT_TH)
		ft_putstr_fd("Failed create thread\n", STDERR_FILENO);
	else if (flag & FAILURE & FAILED_JOIN_TH)
		ft_putstr_fd("Failed joining thread\n", STDERR_FILENO);
	else if (flag & FAILURE & FAILED_KILL)
		ft_putstr_fd("Failed kill\n", STDERR_FILENO);
	else if (flag & FAILURE & FAILED_GET_TIME)
		ft_putstr_fd("Failed get_time\n", STDERR_FILENO);
	else if (flag & FAILURE & FAILED_USLEEP)
		ft_putstr_fd("Failed usleep\n", STDERR_FILENO);
	return (0);
}

void	*free_infos(t_infos *infos, int flag)
{
	if (flag & CLOSE_SEM_FORKS)
		sem_close_safe(infos->forks);
	if (flag & CLOSE_SEM_PRINT)
		sem_close_safe(infos->print);
	if (flag & CLOSE_SEM_TIME)
		sem_close_safe(infos->time);
	if (flag & CLOSE_SEM_DIED)
		sem_close_safe(infos->died);
	if (flag & CLOSE_SEM_MEALS)
		sem_close_safe(infos->meals);
	ft_puterror(flag);
	if (flag & EXIT_FLAG)
		exit(-(flag & FAILURE));
	return (NULL);
}

void	end_dinners_from_main(t_infos *infos, int flag)
{
	int	i;

	if (flag & FAILURE)
	{
		ft_putstr_fd("Philo ", 2);
		ft_putnbr_fd(infos->id, 2);
		ft_putstr_fd(" ERROR\t\t", 2);
		ft_puterror(flag);
	}
	i = -1;
	while (++i < infos->total)
	{
		if (kill(infos->pids[i], SIGTERM) == -1)
			ft_puterror(FAILED_KILL);
	}
	free_infos(infos, flag & ~FAILURE);
	exit (flag & FAILURE);
}

void	end_dinner_meals(t_infos *infos)
{
	sem_post_safe(infos->meals, infos);
	free_infos(infos, CLOSE_ALL | EXIT_FLAG);
}

void	end_dinner_death(t_infos *infos, int flag)
{
	sem_post_safe(infos->died, infos);
	free_infos(infos, flag | CLOSE_ALL | EXIT_FLAG);
}
