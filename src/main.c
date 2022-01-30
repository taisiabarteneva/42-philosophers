# include "philo.h"

void *lifetime(void	*thread)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)thread;
	while (1)
	{
		pthread_mutex_lock(&philo->max->mutex);

		print_mutex("Philo has taken a fork\n", philo->stdout_mutex);

		pthread_mutex_lock(&philo->min->mutex);
		print_mutex("Philo has taken a fork\n", philo->stdout_mutex);
		
		print_mutex("Philo is eating\n", philo->stdout_mutex);

		usleep(philo->time_to_eat * 1000); // eating time

		gettimeofday(&philo->last_meal_time, NULL);
		
		pthread_mutex_unlock(&philo->min->mutex);
		pthread_mutex_unlock(&philo->max->mutex);

		print_mutex("Philo is sleeping\n", philo->stdout_mutex);

		usleep(philo->time_to_sleep * 1000); // sleeping time

		print_mutex("Philo is thinking\n", philo->stdout_mutex);

	}
	return (NULL);
}

void	print_mutex(const char *str, t_mutex *stdout_mutex)
{
	pthread_mutex_lock(stdout_mutex);
	printf("%s", str);
	pthread_mutex_unlock(stdout_mutex);
}

void *spectate(void *data)
{
	t_data 		*new;
	t_timeval	curr;
	int 		i;

	new = (t_data *)data;
	while (1)
	{
		i = 0;
		while (i < new->constants.num_philo)
		{
			gettimeofday(&curr, NULL);
			if (curr.tv_usec - new->philos[i]->last_meal_time.tv_usec > new->constants.time_to_die * 1000) 
			{
				pthread_mutex_lock(&new->stdout_mutex);
				printf("Philosopher is dead.\n");
				exit(0);
			}
			i++;
		}
	}
}

int main(int ac, char *av[])
{
	t_data		*data;

	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo <num_of_philo time_to_die time_to_sleep"
			   " [number_of_times_each_philosopher_must_eat]\n");
		return (SUCCESS);
	}
	if (check(ac, av) == FAILURE) 
		return (SUCCESS);	
	if ((data = init_data(av)) == NULL)
		return (FAILURE);

	pthread_mutex_init(&data->stdout_mutex, NULL);
	pthread_mutex_init(&data->max.mutex, NULL);
	pthread_mutex_init(&data->max.mutex, NULL);
	if (init_threads(data) == FAILURE)
		return (free_all(data));
	spectate(data);

	// if (end_threads(data) == FAILURE)
	// 	return (free_all(data));
	return (SUCCESS);
}