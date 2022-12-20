/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/20 06:21:58 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include "philo_structs.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// crawling.c
void	init_args(t_args *args, int ac, char **av);
void	*init_philo(t_args *args);
void	ft_puterror(int flag);
void	*free_philo(t_args *args, int flag);

// utils.c
void	ft_putstr_fd(char *s, int fd);
unsigned int	ft_atoi_ph(const char *str);

// walking.c
void	*philosophers(void *philo);

#endif