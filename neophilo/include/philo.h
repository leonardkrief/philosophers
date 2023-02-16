/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/16 19:12:22 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# include "error.h"

# define MAX_PHILOS		200
# define MAX_TIMER		60 * 1e6

# define USERGUIDE		"usage:\n\t./philo {nb_philos} {die_tm} \
{eat_tm} {sleep_tm} (max_eat)\n\
\ttime inputs are capped to 60,000 ms\n"

# define	DEATH_MSG	"died\n"
# define	EAT_MSG		"is eating\n"
# define	SLEEP_MSG	"is sleeping\n"
# define	THINK_MSG	"is thinking\n"

typedef struct s_shared_data{
	int		total_philos;
	int		die_timer;
	int		eat_timer;
	int		slp_timer;
	int		max_meals;
	double	init_time;			//temps a l'init
	bool	forks[MAX_PHILOS];	//tableau de fourchettes: 0 si la fourchette est libre, 1 sinon
	bool	death_bool;			//Booleen qui vaut 0 si aucun philo n'est mort, 1 sinon
	pthread_mutex_t	*mutex_forks[MAX_PHILOS];	//tableau de mutex pour proteger les forks
	pthread_mutex_t	*print;		//mutex sur le print pour eviter que 2 philos print en meme temps
	pthread_mutex_t	*keeper;		
	pthread_mutex_t	*death;		//mutex sur la modification de death_bool (eviter les data races si 2 philos meurent en meme temps)
}	t_shared_data;

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

// init.c
int	shared_data(t_shared_data *sh, int ac, char **av);

// error.c
int	ft_putstr_error(const char *s);
const char	*get_failure_string(const t_failure failure);
void	ft_puterror(const t_failure failure_set, const void *args);

// mutex_safe.c
int	pthread_mutex_init_safe(pthread_mutex_t *mutex);
int	pthread_mutex_destroy_safe(pthread_mutex_t *mutex);
int	pthread_mutex_lock_safe(pthread_mutex_t *mutex);
int	pthread_mutex_unlock_safe(pthread_mutex_t *mutex);

// time.c
long	gettime_ms(void);
long	gettime_us(void);
long	converttime_ms(struct timeval tp);
long	converttime_us(struct timeval tp);

// utils.c
int	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
int	ft_atoi_ph(const char *str);
int	printlock(t_philo *ph, char *str, int i);
void	ft_usleep(long time_ms);

#endif