#include "philo.h"

void	dine(t_philosopher *philo, t_mutex *min, t_mutex *max, long time)
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
		pthread_mutex_unlock(max);
		pthread_mutex_unlock(min);
}

void	cycle(t_philosopher *philo, t_mutex *min, t_mutex *max, long time)
{
	while (1)
	{
		dine(philo, min, max, time);
		print_mutex(philo, SLEEPING, philo->num, time);
		custom_usleep(philo->constants->time_to_sleep);
		print_mutex(philo, THINKING, philo->num, time);
		pthread_mutex_lock(&philo->dead);
		if (philo->must_die == 1)
		{
			pthread_mutex_unlock(&philo->dead);
			break ;
		}
		pthread_mutex_unlock(&philo->dead);
	}
}

void	*lifetime(void *thread)
{
    t_philosopher	*philo;
	t_mutex			*min; 
	t_mutex			*max;
	long 			time;
		
    philo = (t_philosopher *)thread;
	min = &((t_philosopher *)thread)->min->mutex;
	max = &((t_philosopher *)thread)->max->mutex;

	if (philo->min->num > philo->max->num)
	{
		min = &((t_philosopher *)thread)->max->mutex;
		max = &((t_philosopher *)thread)->min->mutex;
	}
	if (philo->num % 2 == 0) 
		usleep(100);
	time = philo->constants->program_start.tv_sec * 1000 +
					+ philo->constants->program_start.tv_usec / 1000;
	
	cycle(philo, min, max, time);
    return (NULL);
}

int		init_threads(t_data *data)
{
    int	i;

    i = 0;
    while (i < data->constants.num_philo)
    {
		if (pthread_create(&data->philos[i].t_id, NULL, &lifetime, (void *)&data->philos[i]) != SUCCESS)
            return (FAILURE);
		// pthread_detach(data->philos[i].t_id);
        i++;
    }
    return (SUCCESS);
}

void join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->constants.num_philo)
	{
		pthread_join(data->philos[i].t_id, NULL);
		i++;
	}
}
