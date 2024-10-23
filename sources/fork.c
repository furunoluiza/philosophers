/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:13:55 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/17 14:36:15 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int take_right_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->right->lock);
    if (philo->right->flag == 0)
    {
        philo->right->flag = 1;
        //print_message(philo, philo->id, 1, philo->main);
        pthread_mutex_unlock(&philo->right->lock);
        return (1);    
    }
    pthread_mutex_unlock(&philo->right->lock);
    return (0);

    /* 
    int took;

    took = 0;
    pthread_mutex_lock(&philo->right->lock);
    if (philo->right->flag == 0)
    {
        philo->right->flag = 1;
        print_message(philo, philo->id, 1, philo->main);
        took = 1;
    }
    pthread_mutex_unlock(&philo->right->lock);
    return (took);
     */
}

int take_left_fork(t_philo *philo)
{
    int took;

    took = 1;
    pthread_mutex_lock(&philo->left->lock);
    if (philo->left->flag == 0)
    {
        philo->left->flag = 1;
        print_message(philo, philo->id, 1, philo->main);
        took = 2;
    }
    pthread_mutex_unlock(&philo->left->lock);
    return (took);
}