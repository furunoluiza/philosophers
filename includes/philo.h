/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:51:09 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/08 17:49:59 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdint.h>

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
    int meals;
    int satisfied;
    long    last_meal_tv;
    t_fork  *right;
    t_fork  *left;
    t_main  *main;
}   t_philo;
//guardar as info de quantas vezes ele comeu e a ultima hora que ele comeu
//flag pra saber se o philo ta satisfeito

typedef struct  s_dinner
{
    int         philos;
    int         die;
    int         eat;
    int         sleep;
    int         num_eat;
}   t_dinner;

//adicionar a info de se todos estão vivos e se todos estão satisfeitos
typedef struct  t_main
{
    int         all_alive;
    int         all_satisfied;
    t_fork      *forks;
    t_philo     *philos;
    t_dinner    *dinner; 
    long        start_time;
    pthread_t   *arbitrator;
    pthread_mutex_t alive_lock;
    pthread_mutex_t satisfied_lock;
}   t_main;

/* ---validate_args--- */
size_t	ft_strlen(const char *s);
long	ft_atol(const char *str);
int validate_args(int argc, char **argv);

/* ---dinner--- */
t_main  *build_main(t_fork *forks, t_philo *philos, t_dinner *dinner);
t_fork *build_forks(t_dinner *dinner);
t_philo *build_philos(t_dinner *dinner, t_fork *forks);
int    validate_dinner(t_dinner *dinner);
t_dinner   *build_dinner(char **argv);

/* ---free--- */
void  destroy_forks(t_fork *forks, int num_forks);
void  free_philos(t_philo *philos);
void	free_dinner(t_dinner *dinner);
void    free_all(t_main *main);

/* ---time--- */
long    get_time(void);
void    my_sleep(long time);

/* ---threads--- */
int create_arbitrator(t_main *main);
int join_arbitrator(t_main *main);
int create_threads(t_main *main);

/* ---routine--- */

/* ---arbitrator--- */
void    *arbitrator_routine(void *arg);

#endif