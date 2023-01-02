/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:19:25 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/02 05:30:36 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_exit(char *str)
{
	printf("%s", str);
	fflush(stdout);
	exit (1);
}

void	print_semvalue(sem_t *sem, int thread_id, pthread_mutex_t *mutex, int *sem_value)
{
	if (pthread_mutex_lock(mutex))
		print_exit("Error mutex lock\n");
	printf("(%d) Sem value % 8d\n", thread_id, *sem_value);
	fflush(stdout);
	if (pthread_mutex_unlock(mutex))
		print_exit("Error mutex unlock\n");
}

void	print_wait(sem_t *sem, int thread_id, pthread_mutex_t *mutex, int *sem_value)
{
	if (pthread_mutex_lock(mutex))
		print_exit("Error mutex lock\n");
	printf("(%d) Waiting sem...\n", thread_id);
	fflush(stdout);
	if (sem_wait(sem) == -1)
		print_exit("Error waiting semaphore\n");
	(*sem_value)--;
	// printf("   %d\n", *sem_value);
	// fflush(stdout);
	if (pthread_mutex_unlock(mutex))
		print_exit("Error mutex unlock\n");
}

void	print_post(sem_t *sem, int thread_id, pthread_mutex_t *mutex, int *sem_value)
{
	int	value;

	if (pthread_mutex_lock(mutex))
		print_exit("Error mutex lock\n");
	printf("(%d) Posting sem...\n", thread_id);
	fflush(stdout);
	if (sem_post(sem) == -1)
		print_exit("Error posting semaphore\n");
	(*sem_value)++;
	// printf("   %d\n", *sem_value);
	// fflush(stdout);
	if (pthread_mutex_unlock(mutex))
		print_exit("Error mutex unlock\n");
}


#define	PROCESSES_NUMBER 4
#define	SEM_FORKS "/mysem"

typedef struct s_routine_args
{
	int				pid_id;
	pthread_mutex_t	*mutex;
	int				*sem_value;
	int				random;
} t_routine_args;

int main(int ac, char **av, char **ev)
{
	in_addr_t		i = 0;
	int				random;
	sem_t			*forks;
	pid_t			pids[PROCESSES_NUMBER];
	int				sem_value = 0;
	pthread_mutex_t mutex;
	t_routine_args	args;

	sem_unlink(SEM_FORKS);
	forks = sem_open(SEM_FORKS, O_CREAT, 0644, sem_value);
	if (forks == SEM_FAILED)
		print_exit("Error opening semaphore\n");
	if (pthread_mutex_init(&mutex, NULL))
		print_exit("Error initializing mutex\n");
	while (i < PROCESSES_NUMBER)
	{
		pids[i] = fork();
		if (pids[i] < 0)
			print_exit("Error forking\n");
		if (pids[i] != 0)
		{
			random = 4 - i;
			printf("(%d) Waiting %ds\n", i, random);
			fflush(stdout);
			usleep(random * 1e6);
			printf("(%d) Done\n", i);
			exit(0);
		}
		i++;
	}
	i = 0;
	while (i < PROCESSES_NUMBER - 2)
	{
		printf("(-1) killing %d\n", pids[i]);
		if (kill(pids[i], SIGTERM) == -1)
			print_exit("Error killing process\n");
		i++;
	}
	i = 0;
	while (i < PROCESSES_NUMBER)
	{
		if (waitpid(pids[i], NULL, 0) == -1)
			print_exit("Error waiting process\n");
		i++;
	}
	i = 0;
	while (i < PROCESSES_NUMBER)
		printf("(-1) pid = %d\n", pids[i++]);
}