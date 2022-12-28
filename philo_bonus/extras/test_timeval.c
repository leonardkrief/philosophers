/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 14:33:22 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/20 16:38:19 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_utimediff(struct timeval	*t1, struct timeval	*t2)
{
	return (1000000 * (t1->tv_sec - t2->tv_sec) + (t1->tv_usec - t2->tv_usec));
}

int main(void)
{
	struct timeval *tp;
	struct timeval *tmp;
	struct timespec *rqtp;

	tp = malloc(sizeof(*tp));
	tmp = malloc(sizeof(*tp));
	rqtp = malloc(sizeof(*rqtp));

	gettimeofday(tmp, NULL);
	nanosleep(rqtp, NULL);
	rqtp->tv_nsec = 100000;
	rqtp->tv_sec = 0;
	for (int i = 0; i < 3; i++)
	{
		gettimeofday(tp, NULL);
		printf("(%2i) %d tpusec %d tmpusec\n", i, tp->tv_usec, tmp->tv_usec);
		while (tp->tv_usec >= tmp->tv_usec)
		{
			gettimeofday(tmp, NULL);
			nanosleep(rqtp, NULL);
			gettimeofday(tp, NULL);
			// printf("(%2i) wait : %d tpusec %d tmpusec\n", i, tp->tv_usec, tmp->tv_usec);
		}
		gettimeofday(tp, NULL);
		printf("(%2i) %ld sec ||| %d usec\n\n", i, tp->tv_sec - tmp->tv_sec, tp->tv_usec - tmp->tv_usec);
		gettimeofday(tmp, NULL);
	}
	free(tp);
	free(tmp);
	free(rqtp);
}