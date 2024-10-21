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
    print_message(philo, philo->id, 3, philo->main);
    my_sleep(philo->sleep);
}

void ft_think(t_philo *philo)
{
    print_message(philo, philo->id, 4, philo->main);
}