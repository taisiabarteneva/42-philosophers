# include "philo.h"

t_data *init_data(char *av[])
{
	t_data *data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->constants.num_philo = ft_atoi(av[1]);
	data->constants.time_to_die = ft_atoi(av[2]);
	data->constants.time_to_eat = ft_atoi(av[3]);
	data->constants.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data->constants.times_each_must_eat = ft_atoi(av[5]);
	else
		data->constants.times_each_must_eat = -1;
	gettimeofday(&data->constants.program_start);
	return (data);
}