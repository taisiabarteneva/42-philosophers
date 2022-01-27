# include "philo.h"

void init_philo(t_data)

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