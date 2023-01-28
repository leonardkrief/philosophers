/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/28 14:27:38 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_structs.h"

// death.c
void	*death_th(void *args);

// dinner.c
void	gets_forks(t_dinner *dinner);
int	eats(t_dinner *dinner);
void	sleeps(t_dinner *dinner);
void	thinks(t_dinner *dinner);
int	new_dinner(int id, t_infos *infos);

// error.c
void	*ft_puterror(int flag, void *args);

// launcher.c
int	launcher(t_infos *infos);
int	main(int ac, char **av);

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

// struct_philo.c
void	free_philo(t_philo *philo);
void	*check_philo(t_philo *philo);
t_philo	*new_philo(t_dinner *dinner, int id);

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