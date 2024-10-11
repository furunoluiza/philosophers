/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_think.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:11:43 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/10 12:11:43 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void ft_sleep(t_philo *philo)
{
    long diff;

    diff = get_time() - philo->last_meal_tv;
    print_message(diff, philo->id, 3, philo->main);
    my_sleep(philo->sleep);
}

void ft_think(t_philo *philo)
{
    long diff;

    diff = get_time() - philo->last_meal_tv;
    print_message(diff, philo->id, 4, philo->main);
}