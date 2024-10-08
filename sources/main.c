/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:25:45 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/08 18:01:01 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *arbitrator_routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    printf("arbitrator criado %d\n", philos[1].sleep);
    return (NULL);
}
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

void    *routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    if (philo->id % 2 != 0)
        usleep(500);
    while (!take_fork(philo))
    {
        usleep(500);
    }
    printf("Philo %d is eating\n", philo->id);
    return (NULL);
}

int create_threads(t_main *main)
{
    int i;
    pthread_t   *threads;
    pthread_t   *arbitrator;

    i = 0;
    main->start_time = get_time();
    threads = malloc(sizeof(pthread_t) * main->dinner->philos);
    arbitrator = malloc(sizeof(pthread_t));
    if(!threads || !arbitrator)
        return (0);
    if (pthread_create(arbitrator, NULL, arbitrator_routine, main->philos) != 0)
        return (printf("Failed to create arbitrator"), 0);
    while(i < main->dinner->philos)
    {
        if (pthread_create(&threads[i], NULL, routine, &main->philos[i]) != 0)
            return (printf("Failed to create philo"), 0);
        i++;
    }
    i = 0;
    while(i < main->dinner->philos)
    {
        if(pthread_join(threads[i], NULL) != 0)
            return (printf("Failed to join philo"), 0);
        i++;
    }
    if(pthread_join(*arbitrator, NULL) != 0)
            return (printf("Failed to join arbitrator"), 0);
    free(threads);
    free(arbitrator);
    return (1);
}

int main(int argc, char **argv)
{
    t_dinner    *dinner;
    t_fork      *forks;
    t_philo     *philos;
    t_main      *main;

    philos = NULL;
    if (!validate_args(argc, argv))
        return (1);
    dinner = build_dinner(argv);
    if (!validate_dinner(dinner))
        return (free_dinner(dinner), 1);
    forks = build_forks(dinner);
    philos = build_philos(dinner, forks);
    main = build_main(forks, philos, dinner);
    if (!create_threads(main))
        return (free_all(main), 1);
    return (free_all(main), 0);
}