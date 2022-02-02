# include "philo.h"


void *lifetime(void *thread)
{
    t_philosopher *philo;
    philo = (t_philosopher *)thread;

    while (1)
    {
        pthread_mutex_lock(&philo->min->mutex);
        print_mutex(philo, 1, philo->num);
		pthread_mutex_lock(&philo->max->mutex);
		print_mutex(philo, 1, philo->num);

		print_mutex(philo, 2, philo->num);
        usleep(philo->constants->time_to_eat * 1000); // EATING TIME

		gettimeofday(&philo->last_meal_time, NULL); // GET LAST EATING TIME 
	
		pthread_mutex_unlock(&philo->min->mutex);
		pthread_mutex_unlock(&philo->max->mutex);
        philo->eat_count++;

		print_mutex(philo, 3, philo->num);

		usleep(philo->constants->time_to_sleep * 1000); // SLEEPING TIME

		print_mutex(philo, 4, philo->num);
    }
    return (NULL);
}

void	print_mutex(t_philosopher *thread, int flag, int num)
{
	pthread_mutex_lock(thread->stdout_mutex);
	if (flag == 1)
		printf("%d Philosopher %d has taken a fork\n", num);
	else if (flag == 2)
		printf("Philosopher %d is eating\n", num);
	else if (flag == 3)
		printf("Philosopher %d is sleeping\n", num);
	else if (flag == 4)
		printf("Philosopher %d is eating\n", num);
	else
		printf("Philosopher %d has died\n", num);
    // if (thread->dead == 0)
	    pthread_mutex_unlock(thread->stdout_mutex);
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
			if (curr.tv_usec - new->philos[i].last_meal_time.tv_usec > new->constants.time_to_die * 1000) 
			{
				print_mutex(&new->philos[i], 7, new->philos[i].num, do_newtime(0));
				exit(0);
			}
			i++;
		}
	}
}
int main(int ac, char *av[])
{
    t_data *data;
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
    /* spectator or someone */
    pthread_mutex_init(&data->stdout_mutex, NULL);
    pthread_mutex_init(&data->max.mutex, NULL);
    pthread_mutex_init(&data->min.mutex, NULL);
    init_threads(data);
    spectate(data);
    join_threads(data);
}