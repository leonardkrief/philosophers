/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/31 02:18:11 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H

# include "philo.h"

# define STDERR_FLAG			0b0000000001000000000
# define EXIT_FLAG				0b0000000010000000000

# define FAILURE				0b0000000000111111111
# define FAILED_CRT_THRD		0b0000000011000000001
# define FAILED_JOIN_THRD		0b0000000011000000010
# define FAILED_DETACH_THRD		0b0000000011000000100
# define FAILED_MALLOC			0b0000000011000001000
# define FAILED_INIT_MUTEX		0b0000000011000010000
# define FAILED_DESTROY_MUTEX	0b0000000011000100000
# define FAILED_MUTEX_LOCK		0b0000000011001000000
# define FAILED_MUTEX_UNLOCK	0b0000000011010000000
# define FAILED_GET_TIME		0b0000000011100000000

# define FREE_ALL				0b0000111100000000000
# define FREE_THREADS			0b0000000100000000000
# define FREE_FORKS				0b0000001000000000000
# define FREE_MUTEX_FORKS		0b0000010000000000000
# define FREE_DEATH				0b0000100000000000000

# define DESTROY_ALL			0b1111000000000000000
# define DESTROY_MUT_PRINT		0b0001000000000000000
# define DESTROY_MUT_KEEPER		0b0010000000000000000
# define DESTROY_MUT_DEATH		0b0100000000000000000
# define DESTROY_MUT_FORKS		0b1000000000000000000

// Philo n°i needs forks n°i and n°i+1 to eat
// Forks are available if it is 1, unavailable if 0

typedef struct s_args{
	int				total;
	int				die_timer;
	int				eat_timer;
	int				slp_timer;
	int				max_eat;
	struct timeval	init_time;
	long			time;
	int				exec;
	int				died;
	int				done;
	pthread_t		*thread;
	unsigned char	*fork;
	pthread_mutex_t	*mut_fork;
	pthread_mutex_t	print;
	pthread_mutex_t	keeper;
	pthread_mutex_t	*death;
}	t_args;

typedef struct s_philo{
	t_args			*args;
	int				id;
	int				ate;
	unsigned char	r_fork;
	unsigned char	l_fork;
	int				dead;
	struct timeval	last_meal;
	pthread_mutex_t	death;
}	t_philo;

#endif