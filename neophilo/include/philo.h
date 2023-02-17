/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2023/02/17 14:58:02 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include "structs.h"

// shared_data.c
int	init_shared_data(t_shared_data *sh, int ac, char **av);
int	init_shared_data_mutexes(t_shared_data *sh);
int	init_shared_data_forks_mutexes(t_shared_data *sh);
int	free_shared_data(t_shared_data *sh);

// mutex_safe.c
int	pthread_mutex_init_safe(pthread_mutex_t *mutex);
int	pthread_mutex_destroy_safe(pthread_mutex_t *mutex);
int	pthread_mutex_lock_safe(pthread_mutex_t *mutex);
int	pthread_mutex_unlock_safe(pthread_mutex_t *mutex);

// pthread_safe.c
int	pthread_create_safe(pthread_t *thread, void *(*start_routine)(void *), void *arg);
int	pthread_join_safe(pthread_t thread);
int	pthread_detach_safe(pthread_t thread);

// utils.c
int	ft_putstr_fd(char *s, int fd);
int	ft_atoi_ph(const char *str);
int	someone_died(t_philo *ph);
int	printlock(t_philo *ph, t_message message);

// time.c
long	gettime_ms(void);
long	gettime_us(void);
long	converttime_ms(struct timeval tp);
long	converttime_us(struct timeval tp);
void	ft_ms_sleep(long time_ms);

// error.c
int	ft_putstr_error(const char *s);
const char	*get_failure_string(const t_failure failure);
void	ft_puterror(const t_failure failure_set, const void *args);

// meal.c
void	*meal(void *philo);
int	gets_forks(t_philo *ph);
int	tries_fork(t_philo *ph, int fork);
void	let_go_forks(t_philo *ph);
int	eats(t_philo *ph);
int	sleeps(t_philo *ph);

// launcher.c
int	launcher(t_shared_data *shared, t_philo *philos);
void	init_philo(t_shared_data *shared, t_philo *philo, int i);


#endif