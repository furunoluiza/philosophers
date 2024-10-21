/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:32:48 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/09 19:32:48 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void    *arbitrator_routine(void *arg)
{
    t_philo *philos = (t_philo *)arg;
    printf("arbitrator criado %d\n", philos[1].sleep);
    //loop que vai entrar em cada filosofo do array, checar se ele morreu ou não 
    //se o tempo que ele comeu pela ultima vez for maior que o tempo que ele tem pra comer
    //se um morrer(se não todos tem garfos disponivel) -> muda a flag(mutex) ou se todos estão satisfeitos -> num_eat -> finaliza o programa
    return (NULL);
}

/*void    *arbitrator_routine(void *arg)
{
    int i;
    t_philo *philos;

    i = 0;
    philos = (t_philo *)arg;
    while (42)
    {
        pthread_mutex_lock(&philos->main->alive_lock);
        if (philos->main->all_alive == 1)
        {
            pthread_mutex_unlock(&philos->main->alive_lock);
            break;
        }
        pthread_mutex_unlock(&philos->main->alive_lock);
        i = 0;
        while(i < philos->philos)
        {
            if ((diff_time(philos) + philos[i].eat) >= philos[i].die)
            {
                pthread_mutex_lock(&philos->main->alive_lock);
                philos->main->all_alive = 1;
                pthread_mutex_unlock(&philos->main->alive_lock);
                print_message(diff_time(&philos[i]), philos[i].id, 5, philos->main);
                return (NULL);
            }
            i++;
        }
    }
    return (NULL);
}*/