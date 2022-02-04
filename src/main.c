/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:42:17 by wurrigon          #+#    #+#             */
/*   Updated: 2022/02/04 21:59:32 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_data	*data;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo <num_of_philo time_to_die time_to_sleep"
			" [number_of_times_each_philosopher_must_eat]\n");
		return (FAILURE);
	}
	if (check(ac, av) == FAILURE)
		return (FAILURE);
	data = init_data(av);
	if (data == NULL)
		return (FAILURE);
	init_threads(data);
	monitor(data);
	return (0);
}
