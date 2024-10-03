/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:33:12 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/03 16:06:11 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int    validate_dinner(t_dinner *dinner)
{
    if (dinner->philos <= 0 || dinner->philos > 200) 
        return(printf("Philosophers: Max = 200 && MIN = 1"), 0);
    if (dinner->die < 60)
        return(printf("Time to die: Max = INT_MAX && MIN = 60"), 0);
    if (dinner->eat < 60)
        return(printf("Time to eat: Max = INT_MAX && MIN = 60"), 0);
    if (dinner->sleep < 60)
        return(printf("Time to sleep: Max = INT_MAX && MIN = 60"), 0);
    return (1);
}

void	free_dinner(t_dinner *dinner)
{
	if (dinner == NULL)
		return ;
    free(dinner);
    dinner = NULL;
}

t_dinner   *build_dinner(char **argv)
{
    t_dinner    *new_dinner;

    new_dinner = malloc(sizeof(t_dinner));
    if (!new_dinner)
        return (NULL);
    new_dinner->philos = ft_atol(argv[1]);
    new_dinner->die = ft_atol(argv[2]);
    new_dinner->eat = ft_atol(argv[3]);
    new_dinner->sleep = ft_atol(argv[4]);
    if (argv[5])
        new_dinner->num_eat = ft_atol(argv[5]);
    else
        new_dinner->num_eat = -1;
    return (new_dinner);
}