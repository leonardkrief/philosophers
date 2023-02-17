/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 22:56:06 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/17 12:35:49 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr_error(const char *s)
{
	return (ft_putstr_fd((char *)s, STDERR_FILENO));
}

const char	*get_failure_string(const t_failure failure)
{
	static const char	*failure_strings[12] = {
	"No failure",
	"Failed malloc",
	"Failed write",
	"Failed usleep",
	"Failed gettimeofday",
	"Failed pthread_create",
	"Failed pthread_detach",
	"Failed pthread_join",
	"Failed pthread_mutex_init",
	"Failed pthread_mutex_destroy",
	"Failed pthread_mutex_lock",
	"Failed pthread_mutex_unlock",};

	return (failure_strings[failure]);
}

void	ft_puterror(const t_failure failure_set, const void *args)
{
	if (failure_set >= NO_FAILURE && failure_set <= LAST_FAILURE)
	{
		ft_putstr_error(get_failure_string(failure_set));
		if (args)
		{
			ft_putstr_error(": ");
			ft_putstr_error((char *)args);
		}
		ft_putstr_error("\n");
	}
}
