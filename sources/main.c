/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:25:45 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/07 16:32:36 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    printf("Philo %d is thinking\n", philo->id);
    return (NULL);
}

int create_threads(t_fork *forks, t_philo *philos, int num_philos)
{
    int i;
    pthread_t   *threads;

    i = 0;
    threads = malloc(sizeof(pthread_t) * num_philos);
    if(!threads)
    {
        destroy_forks(forks, num_philos);
        free_philos(philos);
        return (0);
    }
    while(i < num_philos)
    {
        if (pthread_create(&threads[i], NULL, routine, &philos[i]) != 0)
        {
            printf("Failed to create philo");
            destroy_forks(forks, num_philos);
            free_philos(philos);
            free(threads);
            return (0);
        }
        i++;
    }
    i = 0;
    while(i < num_philos)
    {
        if(pthread_join(threads[i], NULL) != 0)
        {
            printf("Failed to join thread");
            destroy_forks(forks, num_philos);
            free_philos(philos);
            free(threads);
            return (0);
        }
        i++;
    }
    free(threads);
    return (1);
}

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
    if (!create_threads(forks, philos, dinner->philos))
        return (free_dinner(dinner), 1);
    destroy_forks(forks, dinner->philos);
    free_philos(philos);
    free_dinner(dinner);
    return (0);
}