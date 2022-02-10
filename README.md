# 42-philosophers
A solution to dining philosophers problem using threads and mutexes. It is one of the classic problems used to describe synchronization issues in a multithreading program.

## What have I learned
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


![Screen Shot 2022-02-10 at 5 52 13 PM](https://user-images.githubusercontent.com/95509213/153433035-b44bd562-28c2-4342-bd34-92a7a7585015.png)
