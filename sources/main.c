/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:25:45 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/03 16:37:38 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int argc, char **argv)
{
    t_dinner    *dinner;

    if (!validate_args(argc, argv))
        return (1);
    dinner = build_dinner(argv);
    if (!validate_dinner(dinner))
        return (free_dinner(dinner), 1);
    free_dinner(dinner);
    return (0);
}