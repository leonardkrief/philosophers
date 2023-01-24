/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/24 06:27:18 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_structs.h"

// dinner.c
void	gets_forks(t_infos *infos);
int		eats(t_infos *infos);
void	sleeps(t_infos *infos);
void	thinks(t_infos *infos);

// free.c
int		ft_puterror(int flag);
void	*free_infos(t_infos *infos, int flag);
void	end_dinners_from_main(t_infos *infos, int flag);
void	end_dinner_meals(t_infos *infos);
void	end_dinner_death(t_infos *infos, int flag);

// init.c
int		init_infos(t_infos *infos, int ac, char **av);
void	*death_check(void *info);
void	*meals_check(void *info);
void	launch_philo(t_infos *i);
void	*launch_dinners(t_infos *infos);

// protected_sem.c
sem_t	*sem_open_new_safe(const char *name, unsigned int value,
			t_infos *infos, int flag);
sem_t	*sem_open_safe(const char *name, t_infos *infos, int flag);
void	sem_close_safe(sem_t *sem);
void	*sem_wait_safe(sem_t *mysem, t_infos *infos);
void	*sem_post_safe(sem_t *mysem, t_infos *infos);

// utils_1.c
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
int		ft_atoi_ph(const char *str);
void	printlock(t_infos *infos, char *str);
void	ft_usleep(long time_ms);

// utils_2.c
long	get_time(void);
long	get_time_us(void);
long	convert_time(struct timeval tp);
long	convert_time_us(struct timeval tp);

#endif