/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/21 19:06:48 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>
# include "philo_structs.h"

// exec.c
void	launch_philos(t_args *args);
void	gets_forks(t_philo *ph);
void	eats(t_philo *ph);
void	sleeps(t_philo *ph);
int	is_dead(t_philo *ph);
void	*philosophers(void *ph);

// free.c
void	ft_puterror(int flag);
int	free_args(t_args *args, int flag, int nb_mutex);
void	*free_philos(t_args *args, int flag);

// init.c
void	init_args_stack(t_args *args, int ac, char **av);
int	init_args_heap(t_args *args);
int	init_philo(t_args *args, t_philo *philo, int i);

// main.c
int	main(int ac, char **av);

// utils.c
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
unsigned int	ft_atoi_ph(const char *str);
int	set_time(struct timeval *t, int n);
int	ft_utimediff(struct timeval *t1, struct timeval *t2);

#endif