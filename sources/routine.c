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

int ft_eat(t_philo *philo)
{
    if (take_fork(philo))
    {
        philo->last_meal_tv = get_time();
        printf("Philo %d is eating\n", philo->id);
        my_sleep(philo->eat);
        philo->meals += 1;
    }

}

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 != 0)
        usleep(500);
    while (philo->main->all_alive = 0 && philo->main->all_satisfied = 0)//enquanto todos estão vivos ou se não está satisfeito
    {
        ft_eat(philo); //transformar na função de comer (pegar os garfos, comer, guardar o tempo da ultima vez que ele comeu, aumenta a quantidade de vezes que ele comeu)
        //comer
        //dormir -> status e my_sleep (microsec)
        //pensar -> print do pensamento -> preso no lock de comer
    }
    return (NULL);
}