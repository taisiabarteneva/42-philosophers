#include "philo.h"

int init_threads(t_data *data)
{
    int i;

    i = 0;
    while (i < data->constants.num_philo)
    {
		if (pthread_create(&data->philos[i].t_id, NULL, &lifetime, (void *)&data->philos[i]) != SUCCESS)
            return (FAILURE);
		// pthread_detach(data->philos[i].t_id);
        i++;
    }
	i = 0;
	while (i < data->constants.num_philo)
	{
		pthread_join(data->philos[i].t_id, NULL);
		i++;
	}
    return (SUCCESS);
}
