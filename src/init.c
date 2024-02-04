/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 02:43:21 by andie             #+#    #+#             */
/*   Updated: 2024/02/03 10:38:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_program *program, char **argv, int argc)
{
	program->philos_finished_meals = 0;
	program->dead = 0;
	program->num_of_philos = ft_unsigned_atoi(argv[1]);
	program->time_to_die = ft_unsigned_atoi(argv[2]);
	program->time_to_eat = ft_unsigned_atoi(argv[3]);
	program->time_to_sleep = ft_unsigned_atoi(argv[4]);
	program->num_times_to_eat = -1;
	if (argc == 6)
		program->num_times_to_eat = ft_unsigned_atoi(argv[5]);
}

static void	init_philo_res(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		program->philos[i].has_reached_meal_count = 0;
		program->philos[i].id = i;
		program->philos[i].info = program;
		program->philos[i].last_time_meal = get_time_in_ms();
		program->philos[i].dead = &program->dead;
		assign_forks(&program->philos[i]);
		i++;
	}
}

static int	init_philosopher_resources(t_program *program)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	program->philos = malloc(sizeof(t_philo) * program->num_of_philos);
	if (program->philos == NULL)
		return (0);
	init_philo_res(program);
	while (i < program->num_of_philos)
	{
		program->philos[i].meal_lock = malloc(sizeof(pthread_mutex_t));
		if (program->philos[i].meal_lock == NULL)
		{
			while (j < i)
				free(program->philos[j++].meal_lock);
			free(program->philos);
			return (0);
		}
		if (pthread_mutex_init(program->philos[i].meal_lock, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

static int	init_shared_resources(t_program *program)
{
	program->fork_lock = init_forks(program);
	if (program->fork_lock == NULL)
		return (0);
	program->write_lock = malloc(sizeof(pthread_mutex_t));
	if (program->write_lock == NULL)
		return (0);
	if (pthread_mutex_init(program->write_lock, NULL) != 0)
		return (0);
	program->death_lock = malloc(sizeof(pthread_mutex_t));
	if (program->death_lock == NULL)
		return (0);
	if (pthread_mutex_init(program->death_lock, NULL) != 0)
		return (0);
	program->global_meal_lock = malloc(sizeof(pthread_mutex_t));
	if (program->global_meal_lock == NULL)
		return (0);
	if (pthread_mutex_init(program->global_meal_lock, NULL) != 0)
		return (0);
	return (1);
}

int	init_philosophers(t_program *program)
{
	program->start_time = get_time_in_ms();
	if (!init_philosopher_resources(program))
	{
		clean_close(program);
		return (0);
	}
	if (!init_shared_resources(program))
	{
		clean_close(program);
		return (0);
	}
	return (1);
}
