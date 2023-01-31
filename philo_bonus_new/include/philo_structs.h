/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/31 04:37:46 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H

# include "philo.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# if defined(__APPLE__)
#  define O_CREAT_SEM_CROSSPLATFORM 0
# else
#  define O_CREAT_SEM_CROSSPLATFORM O_CREAT
# endif

# define MAX_PHILOS 300

# define SEM_FORKS		"/forks"
# define SEM_PRINT		"/print"
# define SEM_DEATH		"/death"
# define SEM_ERROR		"/error"
# define SEM_STOP		"/stop"
# define SEM_TIME		"/time"
# define SEM_LOCALSTOP	"/lstop"

typedef uint64_t	failure_t;

# define FAILURE_MASK(FCODE) (UINT64_C(1) << (FCODE))

# define NO_FAILURE			UINT64_C(0)
# define FAILED_FORK		UINT64_C(1)
# define FAILED_WAITPID		UINT64_C(2)
# define FAILED_SEM_OPEN	UINT64_C(3)
# define FAILED_SEM_CLOSE	UINT64_C(4)
# define FAILED_SEM_POST	UINT64_C(5)
# define FAILED_SEM_WAIT	UINT64_C(6)
# define FAILED_SEM_UNLINK	UINT64_C(7)
# define FAILED_CREAT_TH	UINT64_C(8)
# define FAILED_JOIN_TH		UINT64_C(9)
# define FAILED_DETAC_TH	UINT64_C(10)
# define FAILED_KILL		UINT64_C(11)
# define FAILED_GET_TIME	UINT64_C(12)
# define FAILED_USLEEP		UINT64_C(13)
# define FAILED_WRITE		UINT64_C(14)
# define USERGUIDE			UINT64_C(15)
# define LAST_FAILURE		USERGUIDE

static const char	*failure_strings[] = {
	"No failure",
	"Failed fork: ",
	"Failed waitpid: ",
	"Failed sem_open: ",
	"Failed sem_close: ",
	"Failed sem_post: ",
	"Failed sem_wait: ",
	"Failed sem_unlink: ",
	"Failed create thread: ",
	"Failed joining thread: ",
	"Failed detach thread: ",
	"Failed kill: ",
	"Failed get_time: ",
	"Failed usleep: ",
	"Failed write: ",
	"    usage:\n\t./philo {nb_philos} {die_tm} {eat_tm} {sleep_tm} [max_eat]\n \tnb_philos    < 300\n \ttimer inputs < 60,000 ms"};

# define is_failure_set(FSET, FCODE) FSET &FAILURE_MASK(FCODE)
# define set_failure(FSET, FCODE) FSET |= FAILURE_MASK(FCODE)

typedef struct s_infos
{
	int				philo_nb;
	int				die_timer;
	int				eat_timer;
	int				slp_timer;
	int				max_meals;
	sem_t			*forks;
	sem_t			*death;
	sem_t			*kill;
	sem_t			*print;
	sem_t			*stop;
	long			init_time;
	struct timeval tp;
	pid_t			pids[MAX_PHILOS];
}					t_infos;

typedef struct s_philo
{
	int				id;
	int				eaten_meals;
	char			semtime_name[10];
	sem_t			*time;
	int				go_through;
	long			last_meal;
	pthread_t		death_thread;
	pthread_t		stop_thread;
}					t_philo;

typedef struct s_dinner
{
	t_infos			*infos;
	t_philo			*philo;
}					t_dinner;

#endif