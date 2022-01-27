# include "philo.h"

int free_all(t_data *data)
{
	if (data && data->philos)
		free(data->philos);
	free(data);
	return (FAILURE);
}
