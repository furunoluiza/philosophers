/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:51:09 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/03 16:04:18 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct  s_dinner
{
    int         philos;
    int         die;
    int         eat;
    int         sleep;
    int         num_eat;
}   t_dinner;

/* ---validate_args--- */
size_t	ft_strlen(const char *s);
long	ft_atol(const char *str);
int validate_args(int argc, char **argv);

/* ---dinner--- */
int    validate_dinner(t_dinner *dinner);
void	free_dinner(t_dinner *dinner);
t_dinner   *build_dinner(char **argv);

#endif