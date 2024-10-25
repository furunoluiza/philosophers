/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:19:36 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/25 16:38:09 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_arbitrator(t_main *main)
{
	pthread_t	*arbitrator;

	arbitrator = malloc(sizeof(pthread_t));
	if (!arbitrator)
		return (0);
	main->arbitrator = arbitrator;
	if (pthread_create(main->arbitrator, NULL,
			arbitrator_routine, main->philos) != 0)
		return (printf("Failed to create arbitrator"), 0);
	return (1);
}

int	join_arbitrator(t_main *main)
{
	if (pthread_join(*main->arbitrator, NULL) != 0)
		return (printf("Failed to join arbitrator"), 0);
	free(main->arbitrator);
	return (1);
}

int	create_threads(t_main *main)
{
	int			i;
	pthread_t	*threads;

	i = 0;
	main->start_time = get_time();
	threads = malloc(sizeof(pthread_t) * main->dinner->philos);
	if (!threads)
		return (0);
	create_arbitrator(main);
	while (i < main->dinner->philos)
	{
		main->philos[i].main = main;
		if (pthread_create(&threads[i], NULL, routine, &main->philos[i]) != 0)
			return (printf("Failed to create philo"), 0);
		i++;
	}
	i = 0;
	while (i < main->dinner->philos)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (printf("Failed to join philo"), 0);
		i++;
	}
	join_arbitrator(main);
	return (free(threads), 1);
}
