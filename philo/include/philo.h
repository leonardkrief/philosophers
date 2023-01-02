/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/02 16:26:23 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_structs.h"

// exec.c
int		gets_forks(t_philo *ph);
int		eats(t_philo *ph);
int		sleeps(t_philo *ph);
int		died(t_philo *ph);
int		check_both_forks(t_philo *p);

// free.c
int		ft_puterror(int flag);
int		setexec_puterror(t_args *args, int value, int flag);
void	destroy_mutex_tab(pthread_mutex_t *tab, int size);
int		free_args(t_args *args, int flag);
int		handle_thread_error(t_args *args, t_philo *ph, int flag);

// init.c
int		init_args_stack(t_args *args, int ac, char **av);
int		init_args_heap(t_args *args);
int		init_args_heap_2(t_args *args);
int		init_philo(t_args *args, t_philo *philo, int i);
int		exec_threads(t_args *args, t_philo *philos);

// main.c
void	*philosophers(void *philo);
void	*check_deaths(void *philos);
int		born_to_kill(t_philo *ph);
int		main(int ac, char **av);

// utils_1.c
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
int		ft_atoi_ph(const char *str);
int		printlock(t_philo *ph, char *str, int i);
void	ft_usleep(long time_ms);

// utils_2.c
long	get_time(void);
long	get_time_us(void);
long	convert_time(struct timeval tp);
long	convert_time_us(struct timeval tp);
int		end_dinner(t_philo *ph);

#endif