/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores_processes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:19:25 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/02 16:09:23 by lkrief           ###   ########.fr       */
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


#define	PROCESSES_NUMBER 5
#define	SEM_FORKS "/mysem"

typedef struct s_routine_args
{
	int				pid_id;
	pthread_mutex_t	*mutex;
	int				*sem_value;
	int				random;
} t_routine_args;

void	*routine(void *args)
{
	t_routine_args	*a;
	sem_t			*sem;

	a = ((t_routine_args *)args);
	sem = sem_open(SEM_FORKS, 0);
	usleep(a->pid_id * 100);
	// printf("(%d) Launch  rand = %3d\n", a->pid_id, a->random);
	fflush(stdout);
	if (a->pid_id < PROCESSES_NUMBER - 2)
		print_post(sem, a->pid_id, a->mutex, a->sem_value);
	else
	{
		print_wait(sem, a->pid_id, a->mutex, a->sem_value);
		print_wait(sem, a->pid_id, a->mutex, a->sem_value);
		print_wait(sem, a->pid_id, a->mutex, a->sem_value);
	}
	exit(0);
}

int main(int ac, char **av, char **ev)
{
	int		i = 0;
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
	srand(time(NULL));
	while (i < PROCESSES_NUMBER)
	{
		args.pid_id = i;
		args.mutex = &mutex;
		args.sem_value = &sem_value;
		args.random = (rand() % 1000);
		pids[i] = fork();
		if (pids[i] < 0)
			print_exit("Error forking\n");
		if (pids[i] == 0)
			routine(&args);
		i++;
	}
	i = 0;
	while (i < PROCESSES_NUMBER)
	{
		if (waitpid(pids[i], NULL, 0) == -1)
			print_exit("Error waiting process\n");
		i++;
	}
}