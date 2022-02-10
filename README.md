# 42-philosophers
A solution to dining philosophers problem using threads and mutexes. It is one of the classic problems used to describe synchronization issues in a multithreading program.

## What did I learn
- Threads
- Synchronization primitives such as mutex and semaphore

I decided to implement an algorithm formulated by Dijkstra due to its simplicity and elegance.

A program takes following arguments:

- number_of_philosophers
- time_to_die (in milliseconds)
- time_to_eat (in milliseconds)
- time_to_sleep (in milliseconds) (optional)

## How to build
```
$> make
```
## How to launch
Run with you parameters, e.g. :
```
$> ./philo 5 800 200 200 7
```
