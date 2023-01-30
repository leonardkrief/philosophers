/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrief <lkrief@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:50:09 by lkrief            #+#    #+#             */
/*   Updated: 2023/01/29 16:45:26 by lkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putstr_error(const char *s)
{
	return (fprintf(stderr, "%s", s));
}

const char* get_failure_string(failure_t failure)
{
    return failure_strings[failure];
}

void *ft_puterror(failure_t failure_set, void *args)
{
    if (failure_set == NO_FAILURE) //no failure set, nothing to do ...
        return NULL;               //unless no failure should be reported too

    //for each failure that is set in failure_set
    for (failure_t n=1; n <= LAST_FAILURE; ++n, failure_set >>= 1) {
        if (failure_set & 1) { //failure n is set, report it
            ft_putstr_error(get_failure_string(n));
            ft_putstr_error((char *)args);
            ft_putstr_error("\n");
        }
    }

    //...

    return NULL;
}