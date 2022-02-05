# 42-philosophers-threads
A solution to dining philosophers problem using threads and mutexes. It is one of the classic problems used to describe synchronization issues in a multithreading program. 
I decided to implement an algorithm formulated by Dijkstra due to its simplicity and elegance. It can be formulated as follows:
A philisopher always takes a lower-numbered fork first and then higher-numbered fork. In this case, if four of the five philosophers simultaneously pick up their lower-numbered fork, only the highest-numbered fork will remain on the table, so the fifth philosopher will not be able to pick up any fork.

A program takes following arguments:
◦ number_of_philosophers
◦ time_to_die (in milliseconds)
◦ time_to_eat (in milliseconds)
◦ time_to_sleep (in milliseconds) (optional)

Built :
$> make

Run like this :
$> ./philo 5 800 200 200 7
