/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_close.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 12:43:02 by andie             #+#    #+#             */
/*   Updated: 2024/02/03 09:54:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//clean_close is responsible for cleaning up resources at the end of the program
//It iterates through each philosopher and destroys their associated mutexes 
//(meal_lock and forks) before finally destroying the global write_lock and
//death_lock mutexes, and then freeing all allocated memory.
static void	clean_meal(t_program *program, int i)
{
	while (i < program->num_of_philos)
	{
		if (program->philos[i].meal_lock != NULL)
		{
			pthread_mutex_destroy(program->philos[i].meal_lock);
			free(program->philos[i].meal_lock);
			program->philos[i].meal_lock = NULL;
		}
		i++;
	}
	free(program->philos);
	program->philos = NULL;
}

static void	clean_philosopher_resources(t_program *program)
{
	int	i;

	i = 0;
	if (program->philos != NULL)
	{
		i = 0;
		clean_meal(program, i);
	}
	if (program->fork_lock != NULL)
	{
		i = 0;
		while (i < program->num_of_philos)
		{
			pthread_mutex_destroy(&program->fork_lock[i]);
			i++;
		}
		free(program->fork_lock);
		program->fork_lock = NULL;
	}
}

static void	clean_program_resources(t_program *program)
{
	if (program->write_lock != NULL)
	{
		pthread_mutex_destroy(program->write_lock);
		free(program->write_lock);
		program->write_lock = NULL;
	}
	if (program->death_lock != NULL)
	{
		pthread_mutex_destroy(program->death_lock);
		free(program->death_lock);
		program->death_lock = NULL;
	}
	if (program->global_meal_lock != NULL)
	{
		pthread_mutex_destroy(program->global_meal_lock);
		free(program->global_meal_lock);
		program->global_meal_lock = NULL;
	}
	if (program->philos != NULL)
		free(program->philos);
	if (program != NULL)
		free(program);
}

void	clean_close(t_program *program)
{
	if (program != NULL)
	{
		clean_philosopher_resources(program);
		clean_program_resources(program);
	}
}
