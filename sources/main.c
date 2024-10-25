/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 16:25:45 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/25 16:30:32 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_dinner	*dinner;
	t_fork		*forks;
	t_philo		*philos;
	t_main		*main;

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
