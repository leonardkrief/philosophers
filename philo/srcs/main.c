/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/25 05:11:03 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosophers(void *philo)
{
	t_philo	*ph;
	t_args	*a;

	ph = (t_philo *)philo;
	a = ph->args;
	while (!died(ph, 0) && (ph->ate++ < a->eat_nb || !a->eat_nb))
	{
		while ((!ph->l_fork || !ph->r_fork) && !died(ph, 0))
			gets_forks(ph);
		// printf("(%d) go2\n", ph->n + 1);
		if (!died(ph, 0))
			eats(ph);
		// printf("(%d) go3\n", ph->n + 1);
		if (!died(ph, 0))
			sleeps(ph);
		// printf("(%d) go4\n", ph->n + 1);
		gettimeofday(&ph->tp, NULL);
		if (!died(ph, 0))
			printf("[%lld] %d is thinking\n",
				ft_utdiff(&ph->tp, &a->start), ph->n + 1);
	}
	return (NULL);
}

void	*check_deaths(void *philos)
{
	unsigned int	i;
	int	trigger;
	t_philo	*ph;

	trigger = 0;
	ph = (*(t_philo **)philos);
	while (!trigger)
	{
		i = 0;
		while (i < ph[0].args->phi_nb && !trigger)
		{
			if (pthread_mutex_lock(&ph[i].args->dead[ph[0].n]))
				ft_puterror(FAILED_MUTEX_LOCK);
			if (ph[i].dead)
				trigger = 1;
			if (pthread_mutex_unlock(&ph[i++].args->dead[ph[0].n]))
				ft_puterror(FAILED_MUTEX_UNLOCK);
		}
		// printf("deaths: (%d) %d   (%d) %d   (%d) %d   (%d) %d\n",
		// 	 ph[0].n + 1, ph[0].dead, ph[1].n + 1, ph[1].dead, 
		// 	 ph[2].n + 1, ph[2].dead, ph[3].n + 1, ph[3].dead);
	}
	i = -1;
	while (++i < ph[0].args->phi_nb)
		died(&ph[i], -1);
	// printf("last deaths: (%d) %d   (%d) %d   (%d) %d   (%d) %d\n",
	// 	ph[0].n + 1, ph[0].dead, ph[1].n + 1, ph[1].dead, 
	// 	ph[2].n + 1, ph[2].dead, ph[3].n + 1, ph[3].dead);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_args	args;
	t_philo	*philos;
	int		flag;

	flag = 0;
	if (ac <= 4)
		ft_putstr_fd("Too few arguments\n", 2);
	else if (ac >= 7)
		ft_putstr_fd("Too much arguments\n", 2);
	else if (ft_atoi_ph(av[1]) <= 1)
		ft_putstr_fd("Not enough philosophers\n", 2);
	else
	{
		init_args_stack(&args, ac, av);
		if (init_args_heap(&args) != 0)
			return (-1);
		philos = malloc(sizeof(*philos) * args.phi_nb);
		if (philos == NULL)
			free_args(&args, FAILED_MALLOC | FREE_ALL);
		flag = exec_threads(&args, philos);
		free(philos);
		free_args(&args, FREE_ALL | DESTROY_ALL);
	}
	return (flag);
}
