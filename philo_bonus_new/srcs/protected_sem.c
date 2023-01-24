/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protected_sem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/24 06:29:28 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

sem_t	*sem_open_new_safe(const char *name, unsigned int value,
			t_infos *infos, int flag)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	if (errno == EEXIST)
	{
		if (sem_unlink(name) == -1)
			end_dinner_death(infos, flag);
		sem = sem_open(name, O_CREAT | O_EXCL, 0644, value);
	}
	if (sem == SEM_FAILED)
		end_dinner_death(infos, flag);
	return (sem);
}

sem_t	*sem_open_safe(const char *name, t_infos *infos, int flag)
{
	sem_t	*sem;

	sem = sem_open(name, O_CREAT_SEM_CROSSPLATFORM);
	if (sem == SEM_FAILED)
		end_dinner_death(infos, flag);
	return (sem);
}

void	sem_close_safe(sem_t	*sem)
{
	if (sem_close(sem) == -1)
		ft_puterror(FAILED_SEM_CLOSE);
}

void	*sem_wait_safe(sem_t *mysem, t_infos *infos)
{
	if (sem_wait(mysem) == -1)
		end_dinner_death(infos, FAILED_SEM_WAIT | CLOSE_ALL);
	return (NULL);
}

void	*sem_post_safe(sem_t *mysem, t_infos *infos)
{
	if (sem_post(mysem) == -1)
		end_dinner_death(infos, FAILED_SEM_POST | CLOSE_ALL);
	return (NULL);
}
