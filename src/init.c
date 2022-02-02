# include "philo.h"

void init_constants(t_constants *constants, char *av[])
{
    constants->num_philo = ft_atoi(av[1]);
    constants->time_to_die = ft_atoi(av[2]);
    constants->time_to_eat = ft_atoi(av[3]);
    constants->time_to_sleep = ft_atoi(av[4]);
    if (av[5])
        constants->times_each_must_eat = ft_atoi(av[5]);
    else
        constants->times_each_must_eat = 0;
    gettimeofday(&constants->program_start, NULL);
    // constants->program_start = do_newtime(0);
}

int init_philos(t_data *data)
{
    int     i;
    int     num;
    
    i = -1;
    num = data->constants.num_philo;
    data->philos = (t_philosopher *)malloc(sizeof(t_philosopher) * num);
    if (!data->philos)
        return (free_all(data));
    memset(data->philos, 0, sizeof(t_philosopher));
    while (i < num)
    {  
        data->philos[i].constants = &data->constants;
        data->philos[i].num = i + 1; 
        data->philos[i].stdout_mutex = &data->stdout_mutex;
		data->philos[i].max = &data->max;
		data->philos[i].min = &data->min;
		gettimeofday(&data->philos[i].last_meal_time, NULL);
        i++;
    }
    return (SUCCESS);
}

t_data *init_data(char *av[])
{
    t_data *data;

    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (NULL);
    memset(data, 0, sizeof(t_data));
    init_constants(&data->constants, av);
    init_philos(data);
    return (data);
}