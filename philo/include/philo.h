/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/20 14:03:30 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo_structs.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

// crawling.c
void	init_args_stack(t_args *args, int ac, char **av);
void	*init_args_heap(t_args *args);
void	ft_puterror(int flag);
void	*free_philos(t_args *args, int flag);

// utils.c
void	ft_putstr_fd(char *s, int fd);
void	*ft_calloc(size_t count, size_t size);
unsigned int	ft_atoi(const char *str);

// walking.c
void	*philosophers(t_philo *philo);

#endif