/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 13:19:25 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/02 01:34:43 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	print_exit(char *str)
{
	printf("%s", str);
	exit (1);
}

void	print_semvalue(sem_t *sem, int thread_id, pthread_mutex_t *mutex, int *sem_value)
{
	if (pthread_mutex_lock(mutex))
		print_exit("Error mutex lock\n");
	printf("(%d) Sem value % 8d\n", thread_id, *sem_value);
	if (pthread_mutex_unlock(mutex))
		print_exit("Error mutex unlock\n");
}

void	print_wait(sem_t *sem, int thread_id, pthread_mutex_t *mutex, int *sem_value)
{
	if (pthread_mutex_lock(mutex))
		print_exit("Error mutex lock\n");
	printf("(%d) Waiting sem...", thread_id);
	fflush(stdout);
	if (sem_wait(sem) == -1)
		print_exit("Error waiting semaphore\n");
	(*sem_value)--;
	printf("   %d\n", *sem_value);
	if (pthread_mutex_unlock(mutex))
		print_exit("Error mutex unlock\n");
}

void	print_post(sem_t *sem, int thread_id, pthread_mutex_t *mutex, int *sem_value)
{
	int	value;

	if (pthread_mutex_lock(mutex))
		print_exit("Error mutex lock\n");
	printf("(%d) Posting sem...", thread_id);
	fflush(stdout);
	if (sem_post(sem) == -1)
		print_exit("Error posting semaphore\n");
	(*sem_value)++;
	printf("   %d\n", *sem_value);
	if (pthread_mutex_unlock(mutex))
		print_exit("Error mutex unlock\n");
}


#define	THREAD_NUMBER 4

typedef struct s_routine_args
{
	sem_t			*forks;
	int				th_id;
	pthread_mutex_t	*mutex;
	int				*sem_value;
	int				random;
} t_routine_args;

void	*routine(void *args)
{
	t_routine_args	*a;

	a = ((t_routine_args *)args);
	printf("(%d) Launch  rand = %d\n", a->th_id, a->random);
	usleep(a->random * 10);
	print_post(a->forks, a->th_id, a->mutex, a->sem_value);
	if (a->random % 4 == 1)
		print_wait(a->forks, a->th_id, a->mutex, a->sem_value);
	print_post(a->forks, a->th_id, a->mutex, a->sem_value);
	if (a->random % 4 == 2)
		print_wait(a->forks, a->th_id, a->mutex, a->sem_value);
	return (NULL);
}

int main(int ac, char **av, char **ev)
{
	in_addr_t		i = 0;
	pthread_t		th[THREAD_NUMBER];
	sem_t			*forks;
	int				sem_value = 0;
	pthread_mutex_t mutex;
	t_routine_args	args[THREAD_NUMBER];

	sem_unlink("/forks");
	forks = sem_open("/forks", O_CREAT, 0644, sem_value);
	if (forks == SEM_FAILED)
		print_exit("Error opening semaphore\n");
	if (pthread_mutex_init(&mutex, NULL))
		print_exit("Error initializing mutex\n");
	srand(time(NULL));
	while (i < THREAD_NUMBER)
	{
		args[i].forks = forks;
		args[i].th_id = i;
		args[i].mutex = &mutex;
		args[i].sem_value = &sem_value;
		args[i].random = (rand() % 1000);
		if (pthread_create(&th[args[i].th_id], NULL, &routine, &args[i]))
			print_exit("Error creating thread\n");
		i++;
	}
	i = 0;
	while (i < THREAD_NUMBER)
	{
		if (pthread_join(th[i], NULL))
			print_exit("Error joining thread\n");
		i++;
	}
	// print_post(forks, i);
	// print_semvalue(forks, i, mutex, &sem_value);
	// print_post(forks, i, mutex, &sem_value);
	// print_wait(forks, i, mutex, &sem_value);
	// print_post(forks, i, mutex, &sem_value);
	// print_wait(forks, i, mutex, &sem_value);
	// print_post(forks, i, mutex, &sem_value);
	// print_wait(forks, i, mutex, &sem_value);
	// print_post(forks, i, mutex, &sem_value);
	// print_post(forks, i, mutex, &sem_value);
	// print_post(forks, i, mutex, &sem_value);
	// print_post(forks, i, mutex, &sem_value);
	// print_post(forks, i, mutex, &sem_value);
}