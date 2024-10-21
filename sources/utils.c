/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:40:59 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/10 11:40:59 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int    mutex_lock(int  flag, pthread_mutex_t lock)
{
    pthread_mutex_lock(&lock);
    if (flag != 1)
        flag = 1;
    pthread_mutex_unlock(&lock);
    if(flag == 1)
        return (1);
    return (0);
}
int return_lock(int  flag, pthread_mutex_t lock)
{
    pthread_mutex_lock(&lock);
    if (flag != 0)
        flag = 0;
    pthread_mutex_unlock(&lock);
    if(flag == 0)
        return (1);
    return (0);
}

void    print_message(t_philo *philo, int id, int message, t_main *main)
{
    long    time;

    time = get_time() - philo->main->start_time;
    mutex_lock(main->message_flag, main->message_lock);
    if (main->message_flag == 0)
    {
        pthread_mutex_lock(&main->alive_lock);
        if (main->all_alive == 0)
        {
            if (message == 1)
                printf("%ld %d has taken a fork\n", time, id);
            if (message == 2)
                printf("%ld %d is eating\n", time, id);
            if (message == 3)
                printf("%ld %d is sleeping\n", time, id);
            if (message == 4)
                printf("%ld %d is thinking\n", time, id);
            pthread_mutex_unlock(&main->alive_lock);
        }
        if (main->all_alive == 1 && message == 5)
            printf("%ld %d died\n", time, id);
        pthread_mutex_unlock(&main->alive_lock);
    }
    return_lock(main->message_flag, main->message_lock);
}