/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 17:14:41 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/18 19:08:10 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>

# define MAX_PHILOS 200
# define MAX_TIMER 60000000

# define USERGUIDE "usage:\t./philo [number_of_philos] [die_timer] \
[eat_timer] [sleep_timer] [optional: max_meals]\n\n\
\tnumber_of_philos is capped to 200 (must be > 0)\n\
\ttimer inputs are in ms and capped to 60,000 ms (must be > 0)\n"

typedef enum e_message
{
	FORK_MESSAGE,
	EAT_MESSAGE,
	SLEEP_MESSAGE,
	THINK_MESSAGE,
	DEAD_MESSAGE,
	LAST_MESSAGE
}					t_message;

typedef enum e_failure
{
	NO_FAILURE,
	FAILED_MALLOC,
	FAILED_WRITE,
	FAILED_USLEEP,
	FAILED_GETTIMEOFDAY,
	FAILED_THREAD_CREATE,
	FAILED_THREAD_DETACH,
	FAILED_THREAD_JOIN,
	FAILED_MUTEX_INIT,
	FAILED_MUTEX_DESTROY,
	FAILED_MUTEX_LOCK,
	FAILED_MUTEX_UNLOCK,
}					t_failure;

# define LAST_FAILURE FAILED_MUTEX_UNLOCK

//forks array: 0 if fork is free, 1 if it is taken
typedef struct s_shared_data
{
	int				total_philos;
	int				die_timer;
	int				eat_timer;
	int				slp_timer;
	int				max_meals;
	int				done_meals;
	double			start_time;
	bool			forks[MAX_PHILOS];
	bool			death_bool;
	bool			error_bool;
	pthread_t		threads[MAX_PHILOS + 1];
	pthread_mutex_t	mutex_forks[MAX_PHILOS];
	pthread_mutex_t	print;
	pthread_mutex_t	keeper;
	pthread_mutex_t	death;
	pthread_mutex_t	error;
}					t_shared_data;

// l/r_fork: 0 if he dont hold the fork, 1 if he does
typedef struct s_philo
{
	t_shared_data	*shared;
	int				id;
	int				meals;
	bool			r_fork;
	bool			l_fork;
	bool			dead;
	double			last_meal;
}					t_philo;

#endif