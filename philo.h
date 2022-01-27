#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>


# define FAILURE 	1
# define SUCCESS 	0
# define MAX_PHILO  199
# define MIN_PHILO  1
# define NUM_PHILO  1
# define MIN_VALUE  0

typedef pthread_mutex_t t_mutex;
typedef struct timeval t_timeval;

typedef struct s_constants
{
	int 			num_philo;
	int 			time_to_die;
	int 			time_to_eat;
	int 			time_to_sleep;
	int 			times_each_must_eat;
	t_timeval		program_start;
}				t_constants;

typedef struct	s_fork
{
	int 	num;
	t_mutex	mutex;
}				t_fork;

typedef struct 	s_philosopher
{
	int			num;
	int			eat_count;
	pthread_t	t_id;
	t_fork		min;
	t_fork		max;
	// t_constants	*data;
	t_timeval	last_meal_time;
	t_mutex		stdout_mutex;
	t_mutex		eating_mutex;
} 				t_philosopher;

typedef struct s_data
{
	t_constants		constants;
	t_philosopher 	**philos;
} 				t_data;

/* parse  */
int		ft_atoi_shell(const char *str);
int 	ft_is_numeric_arg(const char *str);
long	ft_atoi(const char *str);
int 	check(int ac, char *av[]);

/* init */
/* inits t_data struct's field constants */
t_data 	*init_data(char *av[]);

/* threads management*/
/* inits threads in a while loop */
int 	init_threads(t_data *data);
/* joins threads in a while loop */
int 	end_threads(t_data *data);

/* simulates philo's life cycle */
void 	*lifetime(void	*data);

/* frees an array of t_philosopher structs and data struct */
int 	free_all(t_data *data);

#endif
