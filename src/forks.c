/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andie <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 23:11:30 by andie             #+#    #+#             */
/*   Updated: 2024/01/27 23:11:32 by andie            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*init_forks(t_program *program)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = malloc(sizeof(pthread_mutex_t) * program->num_of_philos);
	if (forks == NULL)
		ret_error("malloc fail", program);
	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_mutex_init(&forks[i], 0) != 0)
			ret_error("mutex failure", program);
		i++;
	}
	return (forks);
}

void	assign_forks(t_philo *philo)
{
	philo->forks[0] = philo->id;
	philo->forks[1] = (philo->id + 1) % philo->info->num_of_philos;
	if (philo->id % 2)
	{
		philo->forks[0] = (philo->id + 1) % philo->info->num_of_philos;
		philo->forks[1] = philo->id;
	}
}
