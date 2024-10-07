/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:26:34 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/04 16:53:34 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void  destroy_forks(t_fork *forks, int num_forks)
{
    int i;

    i = 0;
    while (i < num_forks)
    {
        pthread_mutex_destroy(&forks[i].lock);
        i++;
    }
    free(forks);
    forks = NULL;
}

void  free_philos(t_philo *philos)
{
    int i;

    i = 0;
    if (philos == NULL)
      return ;
    free(philos);
    philos = NULL;
}

void	free_dinner(t_dinner *dinner)
{
	  if (dinner == NULL)
		  return ;
    free(dinner);
    dinner = NULL;
}