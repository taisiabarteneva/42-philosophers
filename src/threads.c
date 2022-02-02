#include "philo.h"

int init_threads(t_data *data)
{
    int i;
    i = 1;

    while (i < data->constants.num_philo)
    {
		if (pthread_create(&data->philos[i].t_id, NULL, &lifetime, (void *)&data->philos[i]) != SUCCESS)
            return (FAILURE);
        if (i % 2 == 1)
            usleep(100);
        i++;
    }
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