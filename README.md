# philosophers

The problem of five dining philosophers was stated by Edsger Dijkstra. It was designed to illustrate some common issues in concurrent programming. 
So here is my realization of the resource hierarchy solution originally proposed by Dijkstra.

Specific rules in this version are :
- one or more philosophers sit at a round table 
- a philosopher has three states - eating, thinking, sleeping
- a philosopher can eat with two forks
- every fork's state should be protected with a mutex
- each philosopher must be a thread 

Allowed functions :

- memset
- printf
- malloc
- free
- write
- usleep
- gettimeofday
- pthread_create
- pthread_detach
- pthread_join
- pthread_mutex_init
- pthread_mutex_destroy
- pthread_mutex_lock
- pthread_mutex_unlock

Built :
$> make

Usage :
$> ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
