/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/21 18:59:44 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H

# include "philo.h"

# define STDERR_FLAG			0b0000001000000000
# define EXIT_FLAG				0b0000010000000000
# define EXIT_NB				0b0000000111111111
# define FAILED_CRT_THRD		0b0000011000000001
# define FAILED_JOIN_THRD		0b0000011000000010
# define FAILED_DETACH_THRD		0b0000011000000100
# define FAILED_MALLOC			0b0000011000001000
# define FAILED_INIT_MUTEX		0b0000011000010000
# define FAILED_DESTROY_MUTEX	0b0000011000100000
# define FAILED_LOCK_MUTEX		0b0000011001000000
# define FAILED_UNLOCK_MUTEX	0b0000011010000000
# define FAILED_GET_TIME		0b0000011100000000
# define FREE_THREADS			0b0000100000000000
# define FREE_MUTEX				0b0001000000000000
# define FREE_FORKS				0b0010000000000000
# define FREE_LIVES				0b0100000000000000
# define FREE_ONE_MORE			0b1000000000000000
# define FREE_ALL				0b1111100000000000

// Philo n°i needs forks n°i and n°i+1 to eat
// Forks are available if it is 1, unavailable if 0
// life[i] = remaining time to live for philo n°i 
typedef struct s_args{
	unsigned int	phi_nb;
	unsigned int	die_tm;
	unsigned int	eat_tm;
	unsigned int	slp_tm;
	unsigned int	eat_nb;
	pthread_t		*th;
	unsigned char	*fork;
	pthread_mutex_t	*mutex;
}	t_args;

typedef struct s_philo{
	unsigned int	n;
	unsigned int	ate;
	unsigned char	eating;
	t_args			*args;
	struct timeval	*last_meal;
	struct timeval	*tp;
}	t_philo;

#endif