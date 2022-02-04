/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:41:39 by wurrigon          #+#    #+#             */
/*   Updated: 2022/02/05 02:41:27 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi_shell(const char *str)
{
	long	val;

	if (ft_is_numeric_arg(str) == FAILURE)
	{
		printf("Argument must be numeric.\n");
		exit(EXIT_FAILURE);
	}
	val = ft_atoi(str);
	if ((val > (long)INT_MAX + 1 && val < 0) || \
		(val > INT_MAX && val > 0))
	{
		printf("Parameter must be a positive number type of int.\n");
		exit(EXIT_FAILURE);
	}
	return (val);
}

int	check(int ac, char *av[])
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (i == NUM_PHILO && (ft_atoi_shell(av[i]) < MIN_PHILO \
		|| ft_atoi_shell(av[i]) > MAX_PHILO))
		{
			printf("Number of philosophers can't be less than"
				" 1 and more than 199.\n");
			return (FAILURE);
		}
		if ((i == 2 || i == 3 || i == 4) && ft_atoi_shell(av[i]) < 60)
		{
			printf("Philosophers activity must have "
				"a duration of 60 ms at least.\n");
			return (FAILURE);
		}
		if (ft_atoi_shell(av[i]) <= MIN_VALUE)
		{
			printf("Parameter must be a positive number type of int.\n");
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
