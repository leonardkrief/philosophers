/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/30 16:43:39 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_structs.h"

// threads.c
void	*death_th(void *args);
void	*stop_th(void *args);

// dinner.c
int		gets_forks(t_dinner *dinner);
int		eats(t_dinner *dinner);
void	sleeps(t_dinner *dinner);
void	thinks(t_dinner *dinner);
int	new_philo(int id, t_infos *infos);

// error.c
void *ft_puterror(failure_t failure_set, void *args);

// launcher.c
int	launcher(t_infos *infos);
int	finish_dinner(t_infos *infos);

// semaphores_safe.c
sem_t	*sem_open_new_safe(const char *name, unsigned int value);
sem_t	*sem_open_safe(const char *name);
int	sem_close_safe(sem_t *sem);
int	sem_wait_safe(sem_t *sem);
int	sem_post_safe(sem_t *sem);

// struct_infos.c
void	free_infos(t_infos *infos);
void	*check_infos(t_infos *i);
t_infos	*new_infos(t_infos *infos, int ac, char **av);

// struct_dinner.c
void	free_dinner(t_dinner *dinner);
void	*check_dinner(t_dinner *dinner);
void	get_semname(char *sem, char *name, int id);
t_dinner	*new_dinner(t_dinner *dinner, int id);

// time.c
long	gettime_ms(void);
long	gettime_us(void);
long	converttime_ms(struct timeval tp);
long	converttime_us(struct timeval tp);

// utils.c
int	ft_putstr_fd(char *s, int fd);
int	ft_putnbr_fd(int nb, int fd);
int	ft_atoi_philos(const char *str);
void	printlock(t_dinner *dinner, char *str);
void	ft_usleep(long time_ms);

#endif