/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 04:41:31 by lkrief            #+#    #+#             */
/*   Updated: 2022/12/24 12:50:05 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void	*philosophers(void *philo)
{
	t_philo	*ph;
	t_args	*a;

	ph = (t_philo *)philo;
	a = ph->args;
	while (!check_dead(ph) && (ph->ate++ < a->eat_nb || !a->eat_nb))
	{
		while ((!ph->l_fork || !ph->r_fork) && !check_dead(ph))
			gets_forks(ph);
		if (!check_dead(ph))
			eats(ph);
		if (!check_dead(ph))
			sleeps(ph);
		gettimeofday(&ph->tp, NULL);
		if (!check_dead(ph))
			printf("[%lld] %d is thinking\n",
				ft_utdiff(&ph->tp, &a->start), ph->n + 1);
	}
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
		fflush(stderr);
		free(philos);
		free_args(&args, FREE_ALL | DESTROY_ALL);
	}
	return (flag);
}
