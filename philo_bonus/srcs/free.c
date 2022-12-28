/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/28 17:06:24 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_puterror(int flag)
{
	if ((flag & FAILURE & FAILED_CRT_THRD) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed creating thread\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_JOIN_THRD) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed joining thread\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_DETACH_THRD) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed detaching thread\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_MALLOC) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed malloc\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_INIT_MUTEX) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed init mutex\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_DESTROY_MUTEX) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed destroy mutex\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_MUTEX_LOCK) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed lock mutex\n", STDERR_FILENO);
	else if ((flag & FAILURE & FAILED_MUTEX_UNLOCK) && (flag & STDERR_FLAG))
		ft_putstr_fd("Failed unlock mutex\n", STDERR_FILENO);
	return (0);
}

int	setexec_puterror(t_args *args, int value, int flag)
{
	args->exec = value;
	ft_puterror(flag);
	return (value);
}

void	destroy_mutex_tab(pthread_mutex_t *tab, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		if (pthread_mutex_destroy(&tab[i]))
			ft_puterror(FAILED_DESTROY_MUTEX);
	}
}

int	free_args(t_args *args, int flag)
{
	int	i;

	if (flag & DESTROY_MUT_PRINT)
		destroy_mutex_tab(&args->print, 1);
	if (flag & DESTROY_MUT_KEEPER)
		destroy_mutex_tab(&args->keeper, 1);
	if (flag & DESTROY_MUT_FORKS)
		destroy_mutex_tab(args->mutex, args->phi_nb);
	i = 0;
	while ((flag & DESTROY_MUT_DEATH) && i < args->phi_nb)
	{
		if (pthread_mutex_destroy(&args->death[i++].death))
			ft_puterror(FAILED_DESTROY_MUTEX);
	}
	if (flag & FREE_THREADS)
		free(args->th);
	if (flag & FREE_FORKS)
		free(args->fork);
	if (flag & FREE_MUTEX_FORKS)
		free(args->mutex);
	if (flag & FREE_DEATH)
		free(args->death);
	if (!ft_puterror(flag) && (flag & EXIT_FLAG))
		exit(-(flag & FAILURE));
	return (flag & EXIT_FLAG);
}

int	handle_thread_error(t_args *args, t_philo *ph, int flag)
{
	t_args	*a;

	a = args;
	if (a != NULL)
		a = NULL;
	ft_putnbr_fd(ph->n, 2);
	ft_putstr_fd("  ERROR  ", 2);
	ft_puterror(flag);
	return (1);
}
