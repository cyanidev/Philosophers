/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 10:33:04 by andie             #+#    #+#             */
/*   Updated: 2024/02/03 10:42:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//start_simulation here is where we create the threads
void	start_simulation(t_program *program)
{
	int	i;

	i = 0;
	program->start_time = get_time_in_ms();
	while (i < program->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread_id, NULL, \
			(void *)philo_routine, &program->philos[i]) != 0)
			ret_error("Error: pthread_create failed\n", program);
		i++;
	}
	if (pthread_create(&program->observer, NULL, \
		(void *)the_observer, program) != 0)
		ret_error("Error: pthread_create failed\n", program);
}

//at the end of the program, we join the threads and clean up resources
static void	joining_threads(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread_id, NULL) != 0)
			ret_error("Error: pthread_join failed\n", program);
		i++;
	}
	if (pthread_join(program->observer, NULL) != 0)
		ret_error("Error: pthread_join failed\n", program);
	clean_close(program);
}

int	main(int argc, char **argv)
{
	t_program	*info;

	info = malloc(sizeof(t_program) * 1);
	if (info == NULL)
		ret_error("Error: malloc failed\n", info);
	if (argc == 6 || argc == 5)
	{
		if (argcheck(argc, argv) == 0)
			return (EXIT_FAILURE);
		else
		{
			init_data(info, argv, argc);
			if (!init_philosophers(info))
				ret_error("Error: failed\n", info);
			start_simulation(info);
			joining_threads(info);
		}
	}
	else
	{
		printf("try: ./philo <n_of_philos> <time_to_die> <time_to_eat>\
<time _to_sleep> <n_of_times_each_philo_must_eat>\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
