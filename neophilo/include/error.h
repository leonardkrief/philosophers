/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:14:41 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/16 19:03:28 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include <unistd.h>
# include <stdio.h>
# include <stdint.h>

typedef enum e_failure{
	NO_FAILURE,
	FAILED_MALLOC,
	FAILED_WRITE,
	FAILED_USLEEP,
	FAILED_GETTIMEOFDAY,
	FAILED_CRT_THRD,
	FAILED_DETACH_THRD,
	FAILED_JOIN_THRD,
	FAILED_MUTEX_INIT,
	FAILED_MUTEX_DESTROY,
	FAILED_MUTEX_LOCK,
	FAILED_MUTEX_UNLOCK,
}	t_failure;

# define LAST_FAILURE FAILED_MUTEX_UNLOCK

// utils/error_handler/error.c
int			ft_putstr_error(const char *s);
const char	*get_failure_string(const t_failure failure);
void		ft_puterror__uu(const t_failure failure_set, const void *args);

#endif