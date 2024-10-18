/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 16:26:34 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/08 17:41:00 by lfuruno-         ###   ########.fr       */
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
    if (philos == NULL)
        return;
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
void    free_all(t_main *main)
{
    if (main == NULL)
        return ;
    destroy_forks(main->forks, main->dinner->philos);
    free_philos(main->philos);
    free_dinner(main->dinner);
    pthread_mutex_destroy(&main->notsatisfied_lock);
    pthread_mutex_destroy(&main->alive_lock);
    pthread_mutex_destroy(&main->message_lock);
    free(main);
    main = NULL;
}