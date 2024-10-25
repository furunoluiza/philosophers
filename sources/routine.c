/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:21:37 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/09 12:21:37 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int return_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->right->lock);
    if (philo->right->flag == 1)
        philo->right->flag = 0;
    pthread_mutex_unlock(&philo->right->lock);
    pthread_mutex_lock(&philo->left->lock);
    if (philo->left->flag == 1)
        philo->left->flag = 0;
    pthread_mutex_unlock(&philo->left->lock);
    //if(philo->right->flag == 0 && philo->left->flag == 0)
     //   return (0);
    return (1);
}

int    take_fork(t_philo *philo)
{
    int took;

    took = 0;
    if (philo->philos == 1)
        return (1);
    while (took != 2)
    {
        if (took == 0)
            took = take_right_fork(philo);
        if (took == 1)
            took = take_left_fork(philo);
    }
    if (took == 2)
    {
        print_message(philo, philo->id, 2, philo->main);
        pthread_mutex_lock(&philo->live_lock);
        philo->live_tv = get_time() + philo->die;
        pthread_mutex_unlock(&philo->live_lock);
        return (0);
    }
    return (1);
}

int ft_eat(t_philo *philo)
{
    if (!take_fork(philo))
    {
        pthread_mutex_lock(&philo->meals_lock);
        philo->meals += 1;
        pthread_mutex_unlock(&philo->meals_lock);
        my_sleep(philo->eat);
        return_fork(philo);
        return (0);
    }
    return (1);
}

int can_eat(t_philo *philo)
{
    int flag;
    pthread_mutex_lock(&philo->meals_lock);
    if (philo->num_eat == -1 || philo->num_eat > philo->meals)
        flag = 1;
    else
        flag = 0;
    pthread_mutex_unlock(&philo->meals_lock);
    return (flag);
}

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    pthread_mutex_lock(&philo->live_lock);
    philo->live_tv = philo->main->start_time + philo->die;
    pthread_mutex_unlock(&philo->live_lock);
    if (philo->id % 2 != 0)
        my_sleep(200);
    while (can_eat(philo) && philo_alive(philo) == 1 && philo_satisfied(philo) == 1)
    {
        if (ft_eat(philo) == 0)
        {
            ft_sleep(philo);
            ft_think(philo);
        }
    }
    return (NULL);
}
