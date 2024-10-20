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

long    get_last_meal_time(t_philo *philo)
{
    long    last_meal;

    pthread_mutex_lock(&philo->last_meal_lock);
    last_meal = philo->last_meal_tv;
    pthread_mutex_unlock(&philo->last_meal_lock);
    return (last_meal);
}

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
    if(philo->right->flag == 0 && philo->left->flag == 0)
        return (0);
    return (1);
}

int    take_fork(t_philo *philo)
{
    int took;

    took = 0;
    while (took != 2)
    {
        if (took == 0)
            took = take_right_fork(philo);
        if (took == 1)
            took = take_left_fork(philo);
    }
    if (took == 2)
    {
        print_message(diff_time(philo), philo->id, 2, philo->main);
        return (0);
    }
    return (1);
}

int ft_eat(t_philo *philo)
{
    if (!take_fork(philo))
    {
        pthread_mutex_lock(&philo->last_meal_lock);
        philo->last_meal_tv = get_time();
        pthread_mutex_unlock(&philo->last_meal_lock);
        philo->meals += 1;
        my_sleep(philo->eat);
        return_fork(philo);
    }
    return (0);
}
//encerrar a rotina do filosofo quando ele não poder mais comer

void    *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    if (philo->id % 2 != 0)
        usleep(200);
    while (42)
    {
        pthread_mutex_lock(&philo->main->alive_lock);
        pthread_mutex_lock(&philo->main->notsatisfied_lock);
        if ((philo->num_eat != -1 && philo->num_eat <= philo->meals) || 
            philo->main->all_alive == 1 || philo->main->all_not_satisfied == 1) //enquanto todos estão vivos ou se não está satisfeito
        {
            pthread_mutex_unlock(&philo->main->notsatisfied_lock);
            pthread_mutex_unlock(&philo->main->alive_lock);
            break ;
        }
        pthread_mutex_unlock(&philo->main->notsatisfied_lock);
        pthread_mutex_unlock(&philo->main->alive_lock);
        ft_eat(philo);
        ft_sleep(philo);
        ft_think(philo);
        printf("stuck\n");
    }
    return (NULL);
}
