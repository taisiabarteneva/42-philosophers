# include "philo.h"

long int	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	custom_usleep(long int time)
{
	long int	i;

	i = get_time();
	while (get_time() - i < time)
		usleep(10);
}

void *lifetime(void *thread)
{
    t_philosopher	*philo;
	long 			time;

    philo = (t_philosopher *)thread;
	if (philo->num % 2 == 0) 
		usleep(1000);
	time = philo->constants->program_start.tv_sec * 1000 + philo->constants->program_start.tv_usec / 1000;
	while (1)
    {
		pthread_mutex_lock(&philo->left->mutex);
		print_mutex(philo, TAKEN_FORK, philo->num, time);
		pthread_mutex_lock(&philo->right->mutex);

		print_mutex(philo, TAKEN_FORK, philo->num, time);
		print_mutex(philo, EATING, philo->num, time);

		custom_usleep(philo->constants->time_to_eat); 
		gettimeofday(&philo->last_meal_time, NULL);
	
		pthread_mutex_unlock(&philo->left->mutex);
		pthread_mutex_unlock(&philo->right->mutex);
        philo->eat_count++;
		print_mutex(philo, SLEEPING, philo->num, time);

		custom_usleep(philo->constants->time_to_sleep);

		print_mutex(philo, THINKING, philo->num, time);
		if (philo->dead == 1)
			break ;
    }
    return (NULL);
}

void	print_mutex(t_philosopher *thread, int flag, int num, long time)
{
	pthread_mutex_lock(thread->stdout_mutex);
	if (flag == 1)
		printf("%ld philo %d has taken a fork\n", get_time() - time, num);
	else if (flag == 2)
		printf("%ld philo %d is eating\n", get_time() - time, num);
	else if (flag == 3)
		printf("%ld philo %d is sleeping\n", get_time() - time, num);
	else if (flag == 4)
		printf("%ld philo %d is thinking\n", get_time() - time, num);
	else
		printf("%ld philo %d died\n", get_time() - time, num);
    if (thread->dead == 0)
	    pthread_mutex_unlock(thread->stdout_mutex);
}

void *watcher(void *data)
{
	t_data 		*new;
	t_timeval	curr;
	int 		i;
	int			count;

	new = (t_data *)data;
	while (1)
	{
		i = 0;
		count = 0;
		while (i < new->constants.num_philo)
		{
			gettimeofday(&curr, NULL);
			pthread_mutex_lock(&new->philos[i].eating_mutex);
			if ((curr.tv_sec - new->philos[i].last_meal_time.tv_sec) * 1000 + (curr.tv_usec - new->philos[i].last_meal_time.tv_usec)/1000 > new->constants.time_to_die + 5)
			{
				pthread_mutex_unlock(&new->philos[i].eating_mutex);
				new->philos[i].dead = 1;
				print_mutex(&new->philos[i], 7, new->philos[i].num, (new->constants.program_start.tv_sec * 1000 + new->constants.program_start.tv_usec / 1000));
				return (0);
			}
			pthread_mutex_unlock(&new->philos[i].eating_mutex);
			if (new->philos[i].eat_count >= new->constants.times_each_must_eat && new->constants.times_each_must_eat != -222)
				count++;
			if (count == new->constants.num_philo)
				return (0);
			i++;
		}
	}
}

// 1 800 200 200 -
// 5 800 200 200 +
// 5 800 200 200 7 + 
// 4 410 200 200 + !!!!!!!!!!!!!
// 4 310 200 100 -

/* 
TODO
 - my calloc
 - additional arg (times each must eat)
 - add colors to stdout
 - norme
 */

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
    init_threads(data);
    watcher(data);
	exit_program(data);
	return (0);
}