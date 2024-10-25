/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arbitrator.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 19:32:48 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/25 16:20:45 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	num_meals(t_philo *philo)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	if (philo->num_eat == -1)
		return (0);
	while (i < philo->philos)
	{
		pthread_mutex_lock(&philo[i].meals_lock);
		if (philo[i].num_eat <= philo[i].meals)
			counter++;
		pthread_mutex_unlock(&philo[i].meals_lock);
		i++;
	}
	return (counter == philo->philos);
}

void	check_meals(t_philo *philos)
{
	if (num_meals(philos) == 1)
	{
		pthread_mutex_lock(&philos->main->notsatisfied_lock);
		philos->main->all_not_satisfied = 1;
		pthread_mutex_unlock(&philos->main->notsatisfied_lock);
	}
}

int	check_philosopher_lives(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->philos)
	{
		pthread_mutex_lock(&philos[i].live_lock);
		if (philos[i].live_tv <= get_time())
		{
			pthread_mutex_unlock(&philos[i].live_lock);
			pthread_mutex_lock(&philos->main->alive_lock);
			philos->main->all_alive = 1;
			pthread_mutex_unlock(&philos->main->alive_lock);
			print_message(philos, philos[i].id, 5, philos->main);
			return (1);
		}
		pthread_mutex_unlock(&philos[i].live_lock);
		i++;
	}
	return (0);
}

void	*arbitrator_routine(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	my_sleep(200);
	while (42)
	{
		check_meals(philos);
		if (philos->main->all_not_satisfied == 1)
			return (NULL);
		if (check_philosopher_lives(philos))
			return (NULL);
	}
	return (NULL);
}
