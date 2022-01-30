# include "philo.h"

// void init_philo(t_data);

int init_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->constants.num_philo)
	{
		data->philos[i] = (t_philosopher *)malloc(sizeof(t_philosopher));
		if (!data->philos[i])
			return (FAILURE);
		data->philos[i]->num = i;
		data->philos[i]->eat_count = 0;
		data->philos[i]->time_to_die = data->constants.time_to_die;
		data->philos[i]->time_to_sleep = data->constants.time_to_sleep;
		data->philos[i]->time_to_eat = data->constants.time_to_eat;
		data->philos[i]->max = &data->max;
		data->philos[i]->min = &data->min;
		data->philos[i]->stdout_mutex = &data->stdout_mutex;
		gettimeofday(&data->philos[i]->last_meal_time, NULL);

		if (pthread_create(&data->philos[i]->t_id, NULL, 
						&lifetime, (void *)(data->philos[i])) != SUCCESS)
		{
			printf("Can't init thread.");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int end_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->constants.num_philo)
	{
		if (pthread_join(data->philos[i]->t_id, NULL) == FAILURE)
		{
			printf("Can't join a thread.\n");
			return (FAILURE);
		}
		printf("Pthread is joined\n");
		i++;
	}
	return (SUCCESS);
}