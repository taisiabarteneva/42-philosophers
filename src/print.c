# include "philo.h"

// static void	print_message(int flag, int num, long time)
// {
// 	if (flag == TAKEN_FORK)
// 		printf(YELLOW"%ld %d has taken a fork\n"NC, get_time() - time, num);
// 	else if (flag == EATING)
// 		printf(MAGENTA"%ld %d is eating\n"NC, get_time() - time, num);
// 	else if (flag == SLEEPING)
// 		printf(BLUE"%ld %d is sleeping\n"NC, get_time() - time, num);
// 	else if (flag == THINKING)
// 		printf(PINK"%ld %d is thinking\n"NC, get_time() - time, num);
// 	else if (flag == DEAD)
// 	{
// 		printf(GREEN"%ld %d died\n"NC, get_time() - time, num);
// 		// return ;
// 	}
// }

// void	print_mutex(t_philosopher *thread, int flag, int num, long time)
// {
// 	pthread_mutex_lock(thread->stdout_mutex);
// 	print_message(flag, num, time);
// 	pthread_mutex_lock(&thread->dead);
//     if (thread->must_die == 0)
// 	    pthread_mutex_unlock(thread->stdout_mutex);
// 	pthread_mutex_unlock(&thread->dead);
// }