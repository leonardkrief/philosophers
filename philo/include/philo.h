/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/25 04:32:57 by lkrief           ###   ########.fr       */
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
void	gets_forks(t_philo *ph);
void	check_both_forks(t_philo *p);
void	eats(t_philo *ph);
void	sleeps(t_philo *ph);
int	died(t_philo *ph, int flag);

// free.c
void	ft_puterror(int flag);
int	free_args(t_args *args, int flag);
void	handle_thread_error(t_args *args, t_philo *ph, int flag);

// init.c
void	init_args_stack(t_args *args, int ac, char **av);
int	init_args_heap(t_args *args);
int	init_philo(t_args *args, t_philo *philo, int i);
int	exec_threads(t_args *args, t_philo *philos);

// main.c
void	*philosophers(void *philo);
void	*check_deaths(void *philos);
int	main(int ac, char **av);

// utils.c
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	*ft_calloc(size_t count, size_t size);
unsigned int	ft_atoi_ph(const char *str);
long long int	ft_utdiff(struct timeval *t1, struct timeval *t2);

#endif