# include "philo.h"


// void check_all_ate(t_data *data, int i, int *count)
// {
// 	int eat_count;
// 	int must_eat;

// 	eat_count = data->philos[i].eat_count;
// 	must_eat = data->constants.times_each_must_eat;

// 	if (eat_count >= must_eat && must_eat != -222)
// 		(*count)++;
// 	pthread_mutex_unlock(&data->philos[i].eating_mutex);
// 	if (*count == data->constants.num_philo)
// 		return ;
// }

// void set_death_flag(t_data *data)
// {
// 	int	j;

// 	j = 0;
// 	while (j < data->constants.num_philo)
// 	{
// 		pthread_mutex_lock(&data->philos[j].dead);
// 		data->philos[j].must_die = 1;
// 		pthread_mutex_unlock(&data->philos[j].dead);
// 		j++;
// 	}
// }

// void monitor_extra(t_data *data)
// {
// 	int 		i;
// 	int 		count;
// 	t_timeval	curr;
// 	long		time_since_meal;

// 	i = 0;
// 	count = 0;
// 	while (i < data->constants.num_philo)
// 	{
// 		gettimeofday(&curr, NULL);
// 		pthread_mutex_lock(&data->philos[i].eating_mutex);
// 		time_since_meal = find_diff(curr, data->philos[i].last_meal_time);
// 		if (time_since_meal > data->constants.time_to_die)
// 		{
// 			pthread_mutex_unlock(&data->philos[i].eating_mutex);
// 			print_mutex(&data->philos[i], 7, data->philos[i].num, 
// 					convert_time(data->constants.program_start));
// 			set_death_flag(data);
// 			return ;
// 		}
// 		check_all_ate(data, i, &count);
// 		i++;
// 	}
// }

// void *monitor(void *strct)
// {
// 	t_data 		*data;

// 	data = (t_data *)strct;
// 	while (1)
// 	{
// 		monitor_extra(data);
// 	}
// 	join_threads(data);
// 	return (NULL);
// }

void	print_mutex(t_philosopher *thread, int flag, int num, long time)
{
	pthread_mutex_lock(thread->stdout_mutex);
	if (flag == 1)
		printf("%ld %d has taken a fork\n", get_time() - time, num);
	else if (flag == 2)
		printf("%ld %d is eating\n", get_time() - time, num);
	else if (flag == 3)
		printf("%ld %d is sleeping\n", get_time() - time, num);
	else if (flag == 4)
		printf("%ld %d is thinking\n", get_time() - time, num);
	else
	{
		printf("%ld %d died\n", get_time() - time, num);
		return ;
	}
	pthread_mutex_lock(&thread->dead);
    if (thread->must_die == 0)
	    pthread_mutex_unlock(thread->stdout_mutex);
	pthread_mutex_unlock(&thread->dead);
}

void *lifetime(void *thread)
{
    t_philosopher	*philo;
	t_mutex	*min = &((t_philosopher *)thread)->min->mutex;
	t_mutex	*max = &((t_philosopher *)thread)->max->mutex;
	long 			time;

    philo = (t_philosopher *)thread;
	if (philo->min->num > philo->max->num)
	{
		min = &((t_philosopher *)thread)->max->mutex;
		max = &((t_philosopher *)thread)->min->mutex;
	}
	if (philo->num % 2 == 0) 
		usleep(100);
	time = philo->constants->program_start.tv_sec * 1000 + philo->constants->program_start.tv_usec / 1000;
	while (1)
    {
		pthread_mutex_lock(min);
		print_mutex(philo, TAKEN_FORK, philo->num, time);
		pthread_mutex_lock(max);

		print_mutex(philo, TAKEN_FORK, philo->num, time);
		print_mutex(philo, EATING, philo->num, time);

		custom_usleep(philo->constants->time_to_eat); 
		
		pthread_mutex_lock(&philo->eating_mutex);
		gettimeofday(&philo->last_meal_time, NULL);
        philo->eat_count++;
		pthread_mutex_unlock(&philo->eating_mutex);
		print_mutex(philo, SLEEPING, philo->num, time);
		pthread_mutex_unlock(max);
		pthread_mutex_unlock(min);
		custom_usleep(philo->constants->time_to_sleep);
		print_mutex(philo, THINKING, philo->num, time);
		// if (philo->dead == 1)
		// 	break ;
		pthread_mutex_lock(&philo->dead);
		if (philo->must_die == 1)
		{
			pthread_mutex_unlock(&philo->dead);
			return (0);
		}
		pthread_mutex_unlock(&philo->dead);

    }
    return (NULL);
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
		int j = 0;
		count = 0;
		while (i < new->constants.num_philo)
		{
			gettimeofday(&curr, NULL);
			pthread_mutex_lock(&new->philos[i].eating_mutex);
			if ((curr.tv_sec - new->philos[i].last_meal_time.tv_sec) * 1000 + (curr.tv_usec - new->philos[i].last_meal_time.tv_usec)/1000 > new->constants.time_to_die)
			{
				pthread_mutex_unlock(&new->philos[i].eating_mutex);
				print_mutex(&new->philos[i], 7, new->philos[i].num, (new->constants.program_start.tv_sec * 1000 + new->constants.program_start.tv_usec / 1000));
				while (j < new->constants.num_philo)
				{
					pthread_mutex_lock(&new->philos[j].dead);
					new->philos[j].must_die = 1;
					pthread_mutex_unlock(&new->philos[j].dead);
					j++;
				}
				return (0);
			}
			if (new->philos[i].eat_count >= new->constants.times_each_must_eat && new->constants.times_each_must_eat != -222)
				count++;
			pthread_mutex_unlock(&new->philos[i].eating_mutex);
			if (count == new->constants.num_philo)
				return (0);
			i++;
		}
	}
	i = 0;
	while (i < new->constants.num_philo)
	{
		pthread_join(new->philos[i].t_id, NULL);
		i++;
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
    init_threads(data);
    watcher(data);
	exit_program(data);
	return (0);
}