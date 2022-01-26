# include "philo.h"

//memset, printf, malloc, free, write,

//usleep, gettimeofday,

//pthread_create,
//pthread_detach,
//pthread_join,
//pthread_mutex_init,
//pthread_mutex_destroy,
//pthread_mutex_lock,
//pthread_mutex_unlock

void *lifetime(void	*data)
{
	data = (t_data *)data;
	while (1)
	/*=
	{
		lock(min);
		// print about taking the fork
		lock(max);
		// print about taking the fork
		// print about eating
		usleep(eating time * 1000) // dont forget about millisecond (!!!)
		// gettimeofday(&last_eating_time);
		lock(max);
		lock(min);
		// print about sleeping
		usleep(sleeping time * 1000) // dont forget about millisecond (!!!)
		// print about thinking
	}
	*/
	return (NULL);
}

int init_threads(t_data *data)
{
	int i;

	i = 0;
	data->philos = (t_philosopher *)malloc(sizeof(t_philosopher) 
									* data->constants.num_philo);
	if (!data->philos)
	{
		printf("Malloc error\n");
		return (FAILURE);
	}
	while (i < data->constants.num_philo)
	{
		if (pthread_create(&data->philos[i], NULL, lifetime, (void *)data) != 0)
		{
			printf("Can't init thread.");
			return (FAILURE);
		}
		data->philos[i].num = i;
		i++;
	}
}

int main(int ac, char *av[])
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
	if ((data = init_data(av)) == NULL)
		return (FAILURE);
	if (init_threads(data) == FAILURE)
	{
		free(data);
		return (FAILURE);
	}
	// mutex_init(data);


	// check philo
	return (SUCCESS);
}
