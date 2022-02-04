/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:41:53 by wurrigon          #+#    #+#             */
/*   Updated: 2022/02/05 02:37:12 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_constants(t_constants *constants, char *av[])
{
	constants->num_philo = ft_atoi(av[1]);
	constants->time_to_die = ft_atoi(av[2]);
	constants->time_to_eat = ft_atoi(av[3]);
	constants->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		constants->times_each_must_eat = ft_atoi(av[5]);
	else
		constants->times_each_must_eat = -222;
	gettimeofday(&constants->program_start, NULL);
}

int	init_philos(t_data *data)
{
	int	i;
	int	num;

	i = -1;
	num = data->constants.num_philo;
	data->philos = (t_philosopher *)my_calloc(sizeof(t_philosopher), num);
	data->forks = (t_fork *)my_calloc(sizeof(t_fork), num);
	while (++i < num)
		pthread_mutex_init(&(data->forks[i].mutex), NULL);
	i = 0;
	memset(data->philos, 0, sizeof(t_philosopher));
	while (i < num)
	{
		data->philos[i].min = &(data->forks[i]);
		data->philos[i].max = &(data->forks[(i + 1) % num]);
		data->philos[i].constants = &data->constants;
		data->philos[i].num = i + 1;
		data->philos[i].stdout_mutex = &data->stdout_mutex;
		data->philos[i].eat_count = 0;
		gettimeofday(&data->philos[i].last_meal_time, NULL);
		pthread_mutex_init(&data->philos[i].eating_mutex, NULL);
		pthread_mutex_init(&data->philos[i].dead, NULL);
		i++;
	}
	return (SUCCESS);
}

t_data	*init_data(char *av[])
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	memset(data, 0, sizeof(t_data));
	pthread_mutex_init(&data->stdout_mutex, NULL);
	init_constants(&data->constants, av);
	init_philos(data);
	return (data);
}
