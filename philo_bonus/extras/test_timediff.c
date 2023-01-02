/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_timediff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:33:22 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/02 01:09:47 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	ft_utimediff(struct timeval	*t1, struct timeval	*t2)
{
	return (1000000 * (t1->tv_sec - t2->tv_sec) + (t1->tv_usec - t2->tv_usec));
}

int main(void)
{
	struct timeval	*t1;
	struct timeval	*t2;
	struct timespec	*rqtp;
	int				r;

	t1 = malloc(sizeof(*t1));
	t2 = malloc(sizeof(*t2));
	rqtp = malloc(sizeof(*rqtp));
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		r = (rand() % 100);
		gettimeofday(t1, NULL);
		rqtp->tv_nsec = 100000 * r;
		nanosleep(rqtp, NULL);
		gettimeofday(t2, NULL);
		printf("(%d)   r = %2d,   t2 - t1 = %lld msec\n", i, r, ft_utimediff(t2, t1) / 1000);
	}
	free(t1);
	free(t2);
	free(rqtp);
}