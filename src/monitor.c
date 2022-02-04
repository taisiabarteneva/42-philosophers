/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:42:35 by wurrigon          #+#    #+#             */
/*   Updated: 2022/02/05 02:32:18 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_ate(t_data *data, int i, int *count)
{
	int	eat_count;
	int	must_eat;

	eat_count = data->philos[i].eat_count;
	must_eat = data->constants.times_each_must_eat;
	if (eat_count >= must_eat && must_eat != -222)
		(*count)++;
	pthread_mutex_unlock(&data->philos[i].eating_mutex);
	if (*count == data->constants.num_philo)
		return (1);
	return (0);
}

static void	set_death_flag(t_data *data)
{
	int	j;

	j = 0;
	while (j < data->constants.num_philo)
	{
		pthread_mutex_lock(&data->philos[j].dead);
		data->philos[j].must_die = 1;
		pthread_mutex_unlock(&data->philos[j].dead);
		j++;
	}
}

static int	monitor_extra(t_data *data)
{
	int			i;
	int			count;
	t_timeval	curr;
	long		time_since_meal;

	i = 0;
	count = 0;
	while (i < data->constants.num_philo)
	{
		gettimeofday(&curr, NULL);
		pthread_mutex_lock(&data->philos[i].eating_mutex);
		time_since_meal = find_diff(curr, data->philos[i].last_meal_time);
		if (time_since_meal > data->constants.time_to_die)
		{
			pthread_mutex_unlock(&data->philos[i].eating_mutex);
			print_mutex(&data->philos[i], 7, data->philos[i].num,
				convert_time(data->constants.program_start));
			set_death_flag(data);
			return (1);
		}
		if (check_all_ate(data, i, &count) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	*monitor(void *strct)
{
	t_data		*data;

	data = (t_data *)strct;
	while (1)
	{
		if (monitor_extra(data) == 1)
			return (NULL);
	}
	join_threads(data);
	return (NULL);
}
