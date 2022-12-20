/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_structs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:32:36 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/20 06:35:15 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_STRUCTS_H
# define PHILO_STRUCTS_H

# define STDOUT_FLAG 0b100000000
# define STDERR_FLAG 0b1000000000
# define EXIT_FLAG 0b10000000000
# define EXIT_NB 0b11111111
# define FAILED_CRT_THRD 0b1 | STDERR_FLAG | EXIT_FLAG
# define FAILED_JOIN_THRD 0b10 | STDERR_FLAG | EXIT_FLAG
# define FAILED_DETACH_THRD 0b100 | STDERR_FLAG | EXIT_FLAG
# define FAILED_MALLOC_PHILO 0b1000 | STDERR_FLAG | EXIT_FLAG
# define FAILED_INIT_MUTEX 0b10000 | STDERR_FLAG | EXIT_FLAG
# define FAILED_DESTROY_MUTEX 0b100000 | STDERR_FLAG | EXIT_FLAG
# define FAILED_LOCK_MUTEX 0b1000000 | STDERR_FLAG | EXIT_FLAG
# define FAILED_UNLOCK_MUTEX 0b10000000 | STDERR_FLAG | EXIT_FLAG

typedef struct s_args{
	unsigned int	phi_nb;
	unsigned int	die_tm;
	unsigned int	eat_tm;
	unsigned int	slp_tm;
	unsigned int	eat_nb;
	pthread_t		*ph;
	pthread_mutex_t	mutex;
}	t_args;

#endif