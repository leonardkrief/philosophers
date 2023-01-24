/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/24 08:06:39 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h> 
# include "philo.h"

#if defined(__APPLE__)
# define O_CREAT_SEM_CROSSPLATFORM 0
#else
# define O_CREAT_SEM_CROSSPLATFORM O_CREAT
#endif

# define MAX_PHILOS				250

# define SEM_FORKS				"/forks"
# define SEM_PRINT				"/print"
# define SEM_DIED				"/died"
# define SEM_TIME				"/time"
# define SEM_MEALS				"/meals"

# define EXIT_FLAG				0b0000010000000000000

# define FAILURE				0b0000001111111111111
# define FAILED_FORK			0b0000010000000000001
# define FAILED_WAITPID			0b0000010000000000010
# define FAILED_SEM_OPEN		0b0000010000000000100
# define FAILED_SEM_CLOSE		0b0000010000000001000
# define FAILED_SEM_POST		0b0000010000000010000
# define FAILED_SEM_WAIT		0b0000010000000100000
# define FAILED_SEM_UNLINK		0b0000010000001000000
# define FAILED_CREAT_TH		0b0000010000010000000
# define FAILED_JOIN_TH			0b0000010000100000000
# define FAILED_KILL			0b0000010001000000000
# define FAILED_GET_TIME		0b0000010010000000000
# define FAILED_USLEEP			0b0000010100000000000
# define FAILED_WRITE			0b0000011000000000000

# define CLOSE_ALL				0b1111100000000000000
# define CLOSE_SEM_FORKS		0b0000100000000000000
# define CLOSE_SEM_PRINT		0b0001000000000000000
# define CLOSE_SEM_TIME			0b0010000000000000000
# define CLOSE_SEM_DIED			0b0100000000000000000
# define CLOSE_SEM_MEALS		0b1000000000000000000

// Philo n°i needs forks n°i and n°i+1 to eat
// Forks are available if it is 1, unavailable if 0

typedef struct s_infos{
	int				philo_number;
	int				die_timer;
	int				eat_timer;
	int				slp_timer;
	int				max_meals;
	sem_t			*forks;
	sem_t			*death;
	sem_t			*error;
	sem_t			*print;
	struct timeval	init_time;
	pid_t			pids[MAX_PHILOS];
}	t_infos;

typedef struct s_philo{
	int				id;
	int				eaten_meals;
	struct timeval	last_meal;
	pthread_t		dinner_thread;
	pthread_t		death_thread;
	pthread_t		error_thread;
	pthread_t		meals_thread;
}	t_philo;

#endif