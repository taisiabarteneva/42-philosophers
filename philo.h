#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>


# define FAILURE 	1
# define SUCCESS 	0
# define MAX_PHILO  199
# define MIN_PHILO  1
# define NUM_PHILO  1
# define MIN_VALUE  0

# define TAKEN_FORK 1
# define EATING		2
# define SLEEPING	3
# define THINKING	4
# define DEAD		7

# define YELLOW		"\x1B[33m"
# define MAGENTA	"\x1B[34m"
# define BLUE		"\x1B[36m"
# define PINK		"\x1B[35m"
# define GREEN		"\x1B[32m"
# define NC			"\033[0m"

typedef pthread_mutex_t t_mutex;
typedef struct timeval t_timeval;

typedef struct s_constants
{
	int 		num_philo;
	int 		time_to_die;
	int 		time_to_eat;
	int 		time_to_sleep;
	int 		times_each_must_eat;
	t_timeval	program_start;
}				t_constants;

typedef struct	s_fork
{
	int 		num;
	t_mutex		mutex;	
}				t_fork;

typedef struct 	s_philosopher
{
	int 		num;
	int			must_die;
	int			eat_count;
	pthread_t	t_id;
	t_fork		*max;
	t_fork		*min;

	t_constants *constants;
	t_timeval	last_meal_time;
	t_mutex		*stdout_mutex;
	t_mutex		eating_mutex;
	t_mutex		dead;
} 				t_philosopher;

typedef struct s_data
{
	t_constants		constants;
	t_philosopher 	*philos;
	t_mutex			stdout_mutex;
	t_fork			*forks;
	pthread_t		watcher;
} 				t_data;

/* PARSE  */
int		ft_atoi_shell(const char *str);
int 	ft_is_numeric_arg(const char *str);
long	ft_atoi(const char *str);
int 	check(int ac, char *av[]);

/* INIT*/
t_data *init_data(char *av[]);

/* THREADS */
/* inits threads in a while loop */
int 	init_threads(t_data *data);
/* joins threads in a while loop */
void 	join_threads(t_data *data);

/* SIMULATION */
void 	*lifetime(void	*data);

/* MONITOR */
// void 	*monitor(void *data);
void *watcher(void *data);

/* FINISH */
void 	free_all(t_data *data);
void	exit_program(t_data *data);

/* UTILS */
void	custom_usleep(long int time);
long	get_time(void);
long	convert_time(t_timeval val);
long	find_diff(t_timeval val1, t_timeval val2);
void	*my_calloc(size_t size, size_t count);
void	print_mutex(t_philosopher *thread, int flag, int num, long time);

#endif
