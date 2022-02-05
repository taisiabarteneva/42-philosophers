# 42-philosophers-threads
A solution to dining philosophers problem using threads and mutexes. It is one of the classic problems used to describe synchronization issues in a multithreading program.

Due to this projects, I learned more about processes and threads, mutexes and semaphores. 

I decided to implement an algorithm formulated by Dijkstra due to its simplicity and elegance.

A program takes following arguments:

- number_of_philosophers

- time_to_die (in milliseconds)

- time_to_eat (in milliseconds)

- time_to_sleep (in milliseconds) (optional)

Built :
$> make

Run like this :
$> ./philo 5 800 200 200 7
