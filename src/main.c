# include "philo.h"

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
    monitor(data);
	exit_program(data);
	return (0);
}          