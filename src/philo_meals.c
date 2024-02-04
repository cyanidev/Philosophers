/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_meals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andie <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 10:33:48 by andie             #+#    #+#             */
/*   Updated: 2024/02/03 10:33:50 by andie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_is_odd(t_philo *philo)
{
	if (philo->id % 2)
	{
		if (get_time_to_think(philo, 1))
			return (NULL);
	}
	return (NULL);
}

//first we check if is the first time reaching the meal count
//mark that this philosopher has reached the meal count
//if all philosophers have eaten the required number of times
//use the dead flag or another flag to stop the simulation
void	stop_by_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->meal_lock);
	if (philo->meal_count == philo->info->num_times_to_eat)
	{
		if (!philo->has_reached_meal_count)
		{
			philo->has_reached_meal_count = 1;
			pthread_mutex_lock(philo->info->global_meal_lock);
			philo->info->philos_finished_meals++;
			if (philo->info->philos_finished_meals
				== philo->info->num_of_philos)
			{
				pthread_mutex_lock(philo->info->death_lock);
				*(philo->dead) = 1;
				pthread_mutex_unlock(philo->info->death_lock);
			}
			pthread_mutex_unlock(philo->info->global_meal_lock);
		}
	}
	pthread_mutex_unlock(philo->meal_lock);
}

void	*no_meals(t_philo *philo)
{
	while (the_philo_is_dead(philo) != 1)
	{
		if (eat_sleep_routi(philo))
		{
			pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[1]]);
			pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[0]]);
			break ;
		}
		if (the_philo_is_dead(philo))
			return (NULL);
		if (get_time_to_think(philo, 0))
		{
			pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[1]]);
			pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[0]]);
			break ;
		}
	}
	return (NULL);
}

void	*meals(t_philo *philo)
{
	while (philo->meal_count < philo->info->num_times_to_eat)
	{
		if (eat_sleep_ro_cm(philo))
		{
			pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[1]]);
			pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[0]]);
			break ;
		}
		if (the_philo_is_dead(philo))
			return (NULL);
		if (get_time_to_think(philo, 0))
		{
			pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[1]]);
			pthread_mutex_unlock(&philo->info->fork_lock[philo->forks[0]]);
			break ;
		}
	}
	return (NULL);
}
