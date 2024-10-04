/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:51:09 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/04 16:48:00 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct  s_fork
{
    int flag;
    pthread_mutex_t lock;
}   t_fork;

typedef struct  s_philo
{
    int id;
    int philos;
    int die;
    int eat;
    int sleep;
    int num_eat;
    t_fork  *right;
    t_fork  *left;
}   t_philo;

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
t_fork *build_forks(t_dinner *dinner);
t_philo *build_philos(t_dinner *dinner, t_fork *forks);
int    validate_dinner(t_dinner *dinner);
t_dinner   *build_dinner(char **argv);

/* ---free--- */
void  destroy_forks(t_fork *forks, int num_forks);
void  free_philos(t_philo *philos);
void	free_dinner(t_dinner *dinner);

#endif