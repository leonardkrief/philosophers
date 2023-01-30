/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:50:09 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/30 15:51:36 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr_error(const char *s)
{
	return (fprintf(stderr, "%s", s));
}

const char	*get_failure_string(failure_t failure)
{
	return (failure_strings[failure]);
}

void	*ft_puterror(failure_t failure_set, void *args)
{
	if (failure_set == NO_FAILURE || failure_set > LAST_FAILURE)
		return (NULL);
	ft_putstr_error(get_failure_string(failure_set));
	if (args)
		ft_putstr_error((char *)args);
	ft_putstr_error("\n");
	return (NULL);
}