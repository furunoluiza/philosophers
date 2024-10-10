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

int    take_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->right->lock);
    if (philo->right->flag != 1)
        philo->right->flag = 1;
    pthread_mutex_unlock(&philo->right->lock);
    pthread_mutex_lock(&philo->left->lock);
    if (philo->left->flag != 1)
        philo->left->flag = 1;
    pthread_mutex_unlock(&philo->left->lock);
    if(philo->right->flag == 1 && philo->left->flag == 1)
        return (1);
    return (0);
}

int return_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->right->lock);
    if (philo->right->flag != 0)
        philo->right->flag = 0;
    pthread_mutex_unlock(&philo->right->lock);
    pthread_mutex_lock(&philo->left->lock);
    if (philo->left->flag != 0)
        philo->left->flag = 0;
    pthread_mutex_unlock(&philo->left->lock);
    if(philo->right->flag == 0 && philo->left->flag == 0)
        return (1);
    return (0);
}

void    print_message(long time, int id, int message)
{
    if (message == 1)
        printf("%ld %d has taken a fork\n", time, id);
    if (message == 2)
        printf("%ld %d is eating\n", time, id);
    if (message == 3)
        printf("%ld %d is sleeping\n", time, id);
    if (message == 4)
        printf("%ld %d is thinking", time, id);
    if (message == 5)
        printf("%ld %d died", time, id);
}

int ft_eat(t_philo *philo)
{
    long    diff;
    if (take_fork(philo) && (philo->num_eat == -1 || philo->num_eat > philo->meals))
    {
        if (philo->meals <= 0)
            diff = get_time() - philo->main->start_time;
        else
            diff = get_time() - philo->last_meal_tv;
        print_message(diff, philo->id, 1);
        philo->last_meal_tv = get_time();
        if (philo->meals <= 0)
            diff = get_time() - philo->main->start_time;
        else
            diff = get_time() - philo->last_meal_tv;
        print_message(diff, philo->id, 2);
        my_sleep(philo->eat);
        return_fork(philo);
        philo->meals += 1;
    }
    return (0);
}

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 != 0)
        usleep(500);
    while (philo->main->all_alive == 0 && philo->main->all_satisfied == 0)//enquanto todos estão vivos ou se não está satisfeito
    {
        ft_eat(philo); //transformar na função de comer (pegar os garfos, comer, guardar o tempo da ultima vez que ele comeu, aumenta a quantidade de vezes que ele comeu)
        //comer
        //dormir -> status e my_sleep (microsec)
        //pensar -> print do pensamento -> preso no lock de comer
    }
    return (NULL);
}