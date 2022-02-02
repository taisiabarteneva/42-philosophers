#include "philo.h"

void *monitor(void *data)
{
	t_data 	*strct;
	int 	count;
	int 	i;
	strct = (t_data *)data;
	count = 0;
	i = 0;
	while (1)
	{
		count = 0;
		while (i < strct->constants.num_philo)
		{
			if (strct->philos[i].eat_count == strct->constants.times_each_must_eat)
				count++;
			i++;
		}
		if (count == strct->constants.num_philo)
			return (NULL);
	}

	return (NULL);
}

int init_threads(t_data *data)
{
    int i;

    i = 0;
	pthread_create(&data->watcher, NULL, (void*)monitor, data);
    while (i < data->constants.num_philo)
    {
		if (pthread_create(&data->philos[i].t_id, NULL, &lifetime, (void *)&data->philos[i]) != SUCCESS)
            return (FAILURE);
		pthread_detach(data->philos[i].t_id);
        i++;
    }
	pthread_join(data->watcher, NULL);
    return (SUCCESS);
}

int join_threads(t_data *data)
{
	int i;

	i = 0;
	while (i < data->constants.num_philo)
	{
		if (pthread_join(data->philos[i].t_id, NULL) == FAILURE)
		{
			printf("Can't join a thread.\n");
			return (FAILURE);
		}
		printf("Pthread is joined\n");
		i++;
	}
	return (SUCCESS);
}