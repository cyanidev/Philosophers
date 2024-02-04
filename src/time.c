/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andie <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:01:18 by andie             #+#    #+#             */
/*   Updated: 2024/01/10 03:01:22 by andie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time_in_ms(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

void	sim_start_delay(time_t start_time)
{
	while (get_time_in_ms() < start_time)
		continue ;
}

int	philo_sleep(t_philo *philo, time_t sleep_time)
{
	time_t	wake_up;

	wake_up = get_time_in_ms() + sleep_time;
	while (get_time_in_ms() < wake_up)
	{
		pthread_mutex_lock(philo->info->death_lock);
		if (*(philo->dead))
		{
			pthread_mutex_unlock(philo->info->death_lock);
			return (1);
		}
		pthread_mutex_unlock(philo->info->death_lock);
		usleep(100);
	}
	return (0);
}

int	get_time_to_think(t_philo *philo, int flag)
{
	time_t	time_to_think;

	pthread_mutex_lock(philo->meal_lock);
	time_to_think = (philo->info->time_to_die
			- (get_time_in_ms() - philo->last_time_meal)
			- philo->info->time_to_eat) / 2;
	pthread_mutex_unlock(philo->meal_lock);
	if (time_to_think > 600)
		time_to_think = 200;
	if (time_to_think < 0)
		time_to_think = 0;
	if (time_to_think == 0 && flag == 1)
		time_to_think = 1;
	if (flag == 0)
		print_info(philo, 4);
	philo_sleep(philo, time_to_think);
	return (0);
}
