/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 15:33:12 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/08 17:59:17 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_main  *build_main(t_fork *forks, t_philo *philos, t_dinner *dinner)
{
    t_main  *new_main;

    new_main = malloc(sizeof(t_main));
    if (!new_main)
        return (NULL);
    new_main->forks = forks;
    new_main->philos = philos;
    new_main->dinner = dinner;
    new_main->all_not_satisfied = 0;
    pthread_mutex_init(&new_main->notsatisfied_lock, NULL);
    new_main->all_alive = 0;
    pthread_mutex_init(&new_main->alive_lock, NULL);
    new_main->message_flag = 0;
    pthread_mutex_init(&new_main->message_lock, NULL);
    return (new_main);
}

t_fork *build_forks(t_dinner *dinner)
{
    int i;
    t_fork  *forks;

    i = 0;
    forks = malloc(sizeof(t_fork) * dinner->philos);
    if (!forks)
        return (NULL);
    while(i < dinner->philos)
    {
        forks[i].flag = 0;
        pthread_mutex_init(&forks[i].lock, NULL);
        i++;
    }
    return (forks);
}

t_philo *build_philos(t_dinner *dinner, t_fork *forks)
{
    int i;
    t_philo *new_philo;

    i = 0;
    new_philo = malloc(sizeof(t_philo) * dinner->philos);
    if (!new_philo)
        return (free(forks), NULL);
    while(i < dinner->philos)
    {
        new_philo[i].id = i + 1;
        new_philo[i].philos = dinner->philos;
        new_philo[i].die = dinner->die;
        new_philo[i].eat = dinner->eat;
        new_philo[i].sleep = dinner->sleep;
        new_philo[i].num_eat = dinner->num_eat;
        new_philo[i].meals = 0;
        new_philo[i].right = &forks[i];
        new_philo[i].left = &forks[(i + 1) % dinner->philos];
        new_philo[i].main = NULL;
        pthread_mutex_init(&new_philo[i].live_lock, NULL);
        i++;
    }
    return(new_philo);
}

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