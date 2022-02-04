/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wurrigon <wurrigon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:42:53 by wurrigon          #+#    #+#             */
/*   Updated: 2022/02/04 23:44:59 by wurrigon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*my_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	memset(ptr, 0, count * size);
	return (ptr);
}

long int	get_time(void)
{
	t_timeval	t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

void	custom_usleep(long int time)
{
	long	i;

	i = get_time();
	while (get_time() - i < time)
		usleep(10);
}

long	convert_time(t_timeval val)
{
	return (val.tv_sec * 1000 + val.tv_usec / 1000);
}

long	find_diff(t_timeval val1, t_timeval val2)
{
	long	conv_sec;
	long	conv_usec;

	conv_sec = (val1.tv_sec - val2.tv_sec) * 1000;
	conv_usec = (val1.tv_usec - val2.tv_usec) / 1000;
	return (conv_sec + conv_usec);
}
