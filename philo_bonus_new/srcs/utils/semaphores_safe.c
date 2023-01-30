/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_safe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/29 23:57:41 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	*sem_open_new_safe(const char *name, unsigned int value)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (errno == EEXIST)
	{
		if (sem_unlink(name) == -1)
			return (ft_puterror(FAILED_SEM_UNLINK, (char *)name));
		sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	}
	if (sem == SEM_FAILED)
		return (ft_puterror(FAILED_SEM_OPEN, (char *)name));
	return (sem);
}

sem_t	*sem_open_safe(const char *name)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT_SEM_CROSSPLATFORM);
	if (sem == SEM_FAILED)
		return (ft_puterror(FAILED_SEM_OPEN, (char *)name));
	if (sem_unlink(name) == -1)
		return (ft_puterror(FAILED_SEM_UNLINK, (char *)name));
	return (sem);
}

int	sem_close_safe(sem_t *sem)
{
	if (sem_close(sem) == -1)
	{
		ft_puterror(FAILED_SEM_CLOSE, (char *)__func__);
		return (1);
	}
	return (0);
}

int	sem_wait_safe(sem_t *sem)
{
	if (sem_wait(sem) == -1)
	{
		printf("AAAAAAAAAAAA");
		ft_puterror(FAILED_SEM_WAIT, (char *)__func__);
		return (1);
	}
	return (0);
}

int	sem_post_safe(sem_t *sem)
{
	if (sem_post(sem) == -1)
	{
		ft_puterror(FAILED_SEM_POST, (char *)__func__);
		return (1);
	}
	return (0);
}
