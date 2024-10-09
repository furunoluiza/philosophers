/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:22:40 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/08 14:42:20 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long    get_time(void)
{
    struct timeval   tv;

    if (gettimeofday(&tv, NULL))
        return(0);
    return((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void    my_sleep(long time)
{
    long    start_time;

    start_time  = get_time();
    while((get_time() - start_time) < time)
        usleep(500);
}