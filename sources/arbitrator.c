/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:32:48 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/09 19:32:48 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int philo_alive(t_philo *philo)
{
    pthread_mutex_lock(&philo->main->alive_lock);
    if (philo->main->all_alive == 1)
    {
        pthread_mutex_unlock(&philo->main->alive_lock);
        return (0);
    }
        pthread_mutex_unlock(&philo->main->alive_lock);
    return (1);
}

int philo_satisfied(t_philo *philo)
{
    pthread_mutex_lock(&philo->main->notsatisfied_lock);
    if (philo->main->all_not_satisfied == 1)
    {
        pthread_mutex_unlock(&philo->main->notsatisfied_lock);
        return (0);
    }
    pthread_mutex_unlock(&philo->main->notsatisfied_lock);
    return (1);
}

int num_meals(t_philo *philo)
{
    int i;
    int counter;

    i = 0;
    counter = 0;
    if (philo->num_eat == -1)
        return (0);
    while (i < philo->philos)
    {
        pthread_mutex_lock(&philo[i].meals_lock);
        if (philo[i].num_eat <= philo[i].meals)
            counter++;
        pthread_mutex_unlock(&philo[i].meals_lock);
        i++;
    }
    return (counter == philo->philos);
}

void    *arbitrator_routine(void *arg)
{
    int i;
    t_philo *philos;

    i = 0;
    philos = (t_philo *)arg;
    my_sleep(200);
    while (42)
    {
        if (num_meals(philos) == 1)
        {
            pthread_mutex_lock(&philos->main->notsatisfied_lock);
            philos->main->all_not_satisfied = 1;
            pthread_mutex_unlock(&philos->main->notsatisfied_lock);
            return (NULL);
        }
        i = 0;
        while(i < philos->philos)
        {
            pthread_mutex_lock(&philos[i].live_lock);
            if (philos[i].live_tv <= get_time())
            {
                pthread_mutex_unlock(&philos[i].live_lock);
                pthread_mutex_lock(&philos->main->alive_lock);
                philos->main->all_alive = 1;
                pthread_mutex_unlock(&philos->main->alive_lock);
                print_message(philos, philos[i].id, 5, philos->main);
                return (NULL);
            }
            pthread_mutex_unlock(&philos[i].live_lock);
            i++;
        }
    }
    return (NULL);
}
