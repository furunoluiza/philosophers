/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfuruno- <lfuruno-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 14:04:28 by lfuruno-          #+#    #+#             */
/*   Updated: 2024/10/25 16:47:49 by lfuruno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

long	ft_atol(const char *str)
{
	int		sign;
	long	result;
	int		i;

	result = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10;
		result = result + str[i] - '0';
		i++;
	}
	return (result * sign);
}

static int	only_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-')
	{
		printf("Error: All values must be positives");
		return (0);
	}
	if (s[i] == '+')
		i++;
	while (s[i])
	{
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
			printf("Error: All arguments must be a number");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	val_number(int argc, char **argv)
{
	while (--argc > 0)
	{
		if (!only_number(argv[argc]))
			return (0);
		if (ft_strlen(argv[argc]) > 10 || ft_atol(argv[argc]) > 2147483647)
		{
			printf("Error: All values must be an INT");
			return (0);
		}
	}
	return (1);
}

int	validate_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Error: Invalid number of arguments");
		return (0);
	}
	if (!val_number(argc, argv))
		return (0);
	return (1);
}
