/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 11:06:14 by andie             #+#    #+#             */
/*   Updated: 2024/02/03 10:37:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//1 = fork
//2 = eat
//3 = sleep
//4 = think
static void	*one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->fork_lock[philo->forks[0]]);
	print_info(philo, 1);
	usleep(philo->info->time_to_die * 1000);
	pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[0]]);
	return (NULL);
}

int	eat_sleep_routi(t_philo	*philo)
{
	pthread_mutex_lock(&philo->info->fork_lock[philo->forks[0]]);
	print_info(philo, 1);
	pthread_mutex_lock(&philo->info->fork_lock[philo->forks[1]]);
	print_info(philo, 1);
	print_info(philo, 2);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_time_meal = get_time_in_ms();
	pthread_mutex_unlock(philo->meal_lock);
	if (philo_sleep(philo, philo->info->time_to_eat))
		return (1);
	print_info(philo, 3);
	pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[1]]);
	pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[0]]);
	if (philo_sleep(philo, philo->info->time_to_sleep))
		return (1);
	return (0);
}

int	eat_sleep_ro_cm(t_philo	*philo)
{
	pthread_mutex_lock(&philo->info->fork_lock[philo->forks[0]]);
	print_info(philo, 1);
	pthread_mutex_lock(&philo->info->fork_lock[philo->forks[1]]);
	print_info(philo, 1);
	print_info(philo, 2);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_time_meal = get_time_in_ms();
	printf("----------count: %d\n", philo->meal_count);
	philo->meal_count++;
	pthread_mutex_unlock(philo->meal_lock);
	if (philo_sleep(philo, philo->info->time_to_eat))
		return (1);
	print_info(philo, 3);
	stop_by_meal(philo);
	pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[1]]);
	pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[0]]);
	if (philo_sleep(philo, philo->info->time_to_sleep))
		return (1);
	return (0);
}

int	the_philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->info->death_lock);
	if (*(philo->dead))
	{
		pthread_mutex_unlock(philo->info->death_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->info->death_lock);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	if (philo->info->num_times_to_eat == 0)
		return (NULL);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_time_meal = get_time_in_ms();
	pthread_mutex_unlock(philo->meal_lock);
	if (philo->info->num_of_philos == 1)
		return (one_philo(philo));
	sim_start_delay(philo->info->start_time);
	philo_is_odd(philo);
	if (the_philo_is_dead(philo))
		return (NULL);
	if (philo->info->num_times_to_eat == -1)
		no_meals(philo);
	else if (philo->info->num_times_to_eat > 0)
		meals(philo);
	return (NULL);
}
