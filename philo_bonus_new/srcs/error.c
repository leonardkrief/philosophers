/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:50:09 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/28 15:02:45 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr_error(char *s)
{
	return (ft_putstr_fd(s, STDERR_FILENO));
}

void	*ft_puterror_2(int flag, void *args)
{
	if (flag & FAILED_USLEEP)
		ft_putstr_error("Failed usleep: ");
	else if (flag & FAILED_WRITE)
		ft_putstr_error("Failed write: ");
	if (flag & FAILURE)
	{
		ft_putstr_error((char *)args);
		ft_putstr_error("\n");
	}
	if (flag & USERGUIDE)
		ft_putstr_error(USERGUIDE_MSG);
	return (NULL);
}

void	*ft_puterror(int flag, void *args)
{
	if (flag & FAILED_FORK)
		ft_putstr_error("Failed fork: ");
	else if (flag & FAILED_WAITPID)
		ft_putstr_error("Failed waitpid: ");
	else if (flag & FAILED_SEM_OPEN)
		ft_putstr_error("Failed sem_open: ");
	else if (flag & FAILED_SEM_CLOSE)
		ft_putstr_error("Failed sem_close: ");
	else if (flag & FAILED_SEM_POST)
		ft_putstr_error("Failed sem_post: ");
	else if (flag & FAILED_SEM_WAIT)
		ft_putstr_error("Failed sem_wait: ");
	else if (flag & FAILED_SEM_UNLINK)
		ft_putstr_error("Failed sem_unlink: ");
	else if (flag & FAILED_CREAT_TH)
		ft_putstr_error("Failed create thread: ");
	else if (flag & FAILED_JOIN_TH)
		ft_putstr_error("Failed joining thread: ");
	else if (flag & FAILED_KILL)
		ft_putstr_error("Failed kill: ");
	else if (flag & FAILED_GET_TIME)
		ft_putstr_error("Failed get_time: ");
	return (ft_puterror_2(flag, args));
}
