/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 21:42:07 by andie             #+#    #+#             */
/*   Updated: 2024/02/03 10:39:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//checks if any philosopher in the simulation has died due to not eating within 
//a specified time limit (program->time_to_die).
//terates over each philosopher starting from index i up to the total number 
//of philosophers (program->num_of_philos).
//For each philosopher, it locks a mutex associated with that philosopher's 
//last meal time (meal_lock) to ensure exclusive access to this piece of data.
//Checks if the current time minus the philosopher's last meal time is greater 
//than or equal to the time allowed before a philosopher dies from hunger 
//(program->time_to_die).
static void	*check_death(t_program *program, int i)
{
	while (i < program->num_of_philos)
	{
		pthread_mutex_lock(program->philos[i].meal_lock);
		if (get_time_in_ms() - program->philos[i].last_time_meal \
			>= program->time_to_die)
		{
			pthread_mutex_lock(program->philos[i].info->death_lock);
			program->dead = 1;
			pthread_mutex_unlock(program->philos[i].info->death_lock);
			pthread_mutex_unlock(program->philos[i].meal_lock);
			print_info(&program->philos[i], 0);
			return (NULL);
		}
		pthread_mutex_unlock(program->philos[i].meal_lock);
		i++;
	}
	return (NULL);
}

void	*the_observer(void *arg)
{
	t_program	*program;
	int			i;

	i = 0;
	program = (t_program *)arg;
	sim_start_delay(program->start_time);
	while (1)
	{
		pthread_mutex_lock(program->death_lock);
		if (program->dead)
		{
			pthread_mutex_unlock(program->death_lock);
			break ;
		}
		pthread_mutex_unlock(program->death_lock);
		i = 0;
		check_death(program, i);
		usleep(1000);
	}
	return (NULL);
}
