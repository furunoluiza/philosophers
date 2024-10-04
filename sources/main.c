/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:25:45 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/04 16:48:47 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

/*void    *routine(pthread_mutex_t *mutex)
{
    int i = 0;
    while(i < 2)
    {
        pthread_mutex_lock(&mutex);
        i++;
        pthread_mutex_unlock(&mutex);
    }
}

int    create_threads(t_dinner *dinner)
{
    int i;
    pthread_t   philos;
    pthread_mutex_t mutex;

    i = dinner->philos;
    philos = malloc(sizeof(pthread_t) * dinner->philos);
    if(!philos)
        return(NULL);
    pthread_mutex_init(&mutex, NULL);
    while(i > 0)
    {
        if(pthread_create(&philo[i], NULL, routine, mutex) != 0)
        {
            printf("Failed to create philo");
            return (free(philos), 0);
        }
    }
    i = 0;
    while(i > 0)
    {
        if(pthread_join(th[i], NULL) != 0)
            return (free(philos), 0);
    }
    pthread_mutex_destroy(&mutex);
    return (free(philos), 1);
}*/

int main(int argc, char **argv)
{
    t_dinner    *dinner;
    t_fork      *forks;
    t_philo     *philos;

    philos = NULL;
    if (!validate_args(argc, argv))
        return (1);
    dinner = build_dinner(argv);
    if (!validate_dinner(dinner))
        return (free_dinner(dinner), 1);
    forks = build_forks(dinner);
    philos = build_philos(dinner, forks);
    /*if (!create_threads(dinner))
        return (free_dinner(dinner), 1);*/
    destroy_forks(forks, dinner->philos);
    free_philos(philos);
    free_dinner(dinner);
    return (0);
}