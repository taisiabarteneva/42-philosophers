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


void *lifetime(void	*thread)
{
	t_philosopher *philo;
	philo = (t_philosopher *)thread;
	while (1)
	{
		pthread_mutex_init(&philo->max.mutex, NULL);
		pthread_mutex_init(&philo->min.mutex, NULL);
		pthread_mutex_lock(&philo->max.mutex);
		printf("Philosopher %d has taken a fork\n", philo->num);
		pthread_mutex_unlock(&philo->min.mutex);
		printf("Philosopher %d has taken a fork\n", philo->num);		
		printf("Philosopher %d is eating\n", philo->num);		
		usleep(200 * 1000); // eating time
		gettimeofday(&last_meal_time);
		pthread_mutex_unlock(&philo->min.mutex);
		pthread_mutex_unlock(&philo->max.mutex);
		printf("Philosopher %d is sleeping\n", philo->num);		
		usleep(200 * 1000); // sleeping time
		printf("Philosopher %d is thinking\n", philo->num);		
	}
	return (NULL);
}

int main(int ac, char *av[])
{
	t_data	*data;

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
	if (init_threads(data) == FAILURE)
		return (free_all(data));
	if (end_threads(data) == FAILURE)
		return (free_all(data));
	
	// check philo
	return (SUCCESS);
}
