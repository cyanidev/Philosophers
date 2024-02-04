/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:32:26 by andie             #+#    #+#             */
/*   Updated: 2024/02/03 00:45:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_info(t_philo *philo, int action)
{
	pthread_mutex_lock(philo->info->write_lock);
	if (action == 0)
		printf("%ld %d \
died\n", get_time_in_ms() - philo->info->start_time, philo->id + 1);
	pthread_mutex_lock(philo->info->death_lock);
	if (*(philo->dead) == 1)
	{
		pthread_mutex_unlock(philo->info->death_lock);
		pthread_mutex_unlock(philo->info->write_lock);
		return ;
	}
	pthread_mutex_unlock(philo->info->death_lock);
	if (action == 1)
		printf("%ld %d has taken a \
fork\n", get_time_in_ms() - philo->info->start_time, philo->id + 1);
	else if (action == 2)
		printf("%ld %d is \
eating\n", get_time_in_ms() - philo->info->start_time, philo->id + 1);
	else if (action == 3)
		printf("%ld %d is \
sleeping\n", get_time_in_ms() - philo->info->start_time, philo->id + 1);
	else if (action == 4)
		printf("%ld %d is \
thinking\n", get_time_in_ms() - philo->info->start_time, philo->id + 1);
	else if (action == 0)
		printf("%ld %d \
died\n", get_time_in_ms() - philo->info->start_time, philo->id + 1);
	pthread_mutex_unlock(philo->info->write_lock);
}
