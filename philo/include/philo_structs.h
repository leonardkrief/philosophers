/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/26 02:36:46 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H

# include "philo.h"

# define STDERR_FLAG			0b0000001000000000
# define EXIT_FLAG				0b0000010000000000

# define FAILURE				0b0000000111111111
# define FAILED_CRT_THRD		0b0000011000000001
# define FAILED_JOIN_THRD		0b0000011000000010
# define FAILED_DETACH_THRD		0b0000011000000100
# define FAILED_MALLOC			0b0000011000001000
# define FAILED_INIT_MUTEX		0b0000011000010000
# define FAILED_DESTROY_MUTEX	0b0000011000100000
# define FAILED_MUTEX_LOCK		0b0000011001000000
# define FAILED_MUTEX_UNLOCK	0b0000011010000000
# define FAILED_GET_TIME		0b0000011100000000

# define FREE_ALL				0b0111100000000000
# define FREE_THREADS			0b0000100000000000
# define FREE_FORKS				0b0001000000000000
# define FREE_MUTEX_FORKS		0b0010000000000000
# define FREE_MUTEX_DEAD		0b0100000000000000

# define DESTROY_ALL			0b1000000000000000
# define DESTROY_MUTEX			0b1000000000000000

// Philo n°i needs forks n°i and n°i+1 to eat
// Forks are available if it is 1, unavailable if 0

typedef struct t_death t_death;
typedef struct s_args{
	unsigned int	phi_nb;
	unsigned int	die_tm;
	unsigned int	eat_tm;
	unsigned int	slp_tm;
	unsigned int	eat_nb;
	long			start;
	long			time;
	int				exec;
	int				one_died;
	int				plate;
	pthread_t		*th;
	unsigned char	*fork;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	print;
	pthread_mutex_t	keeper;
	t_death			*death;
}	t_args;

typedef struct s_philo{
	t_args			*args;
	unsigned int	n;
	unsigned int	ate;
	unsigned char	r_fork;
	unsigned char	l_fork;
	int				dead;
	pthread_mutex_t	*death;
}	t_philo;

typedef struct t_death
{
	struct timeval	last_meal;
	pthread_mutex_t	death;
}	t_death;

#endif