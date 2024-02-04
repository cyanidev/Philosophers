/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 18:01:25 by afelicia          #+#    #+#             */
/*   Updated: 2024/02/03 10:46:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h> //memset
# include <stdio.h> //printf
# include <stdlib.h> //malloc
# include <unistd.h> //usleep 
# include <sys/time.h>  //gettimeofday
# include <pthread.h> //pthread_Create
# include <limits.h> //max int

struct	s_program;

typedef struct s_philo
{
	struct s_program	*info;
	pthread_t			thread_id;
	unsigned int		id;
	unsigned int		forks[2];
	int					has_reached_meal_count;
	time_t				last_time_meal;
	int					*dead;
	pthread_mutex_t		*meal_lock;
	int					has_left_fork;
	int					has_right_fork;
	int					meal_count;
}	t_philo;

typedef struct s_program
{
	t_philo			*philos;
	pthread_t		observer;
	pthread_mutex_t	*fork_lock;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*death_lock;
	pthread_mutex_t	*global_meal_lock;
	int				num_of_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				philos_finished_meals;
	int				num_times_to_eat;
	time_t			start_time;
	int				dead;
}	t_program;

pthread_mutex_t	*init_forks(t_program *program);
int				main(int argc, char **argv);
int				ret_error(char *str, t_program *program);
int				argcheck(int argc, char **argv);
int				ft_unsigned_atoi(char *str);
void			init_data(t_program *program, char **argv, int argc);
int				init_philosophers(t_program *program);
void			start_simulation(t_program *program);
time_t			get_time_in_ms(void);
void			print_info(t_philo *philo, int action);
int				get_time_to_think(t_philo *philo, int flag);
void			clean_close(t_program *program);
int				philo_sleep(t_philo *philo, time_t sleep_time);
void			*philo_routine(void *arg);
void			assign_forks(t_philo *philo);
void			*the_observer(void *arg);
void			sim_start_delay(time_t start_time);
void			*philo_is_odd(t_philo *philo);
void			stop_by_meal(t_philo *philo);
void			*no_meals(t_philo *philo);
void			*meals(t_philo *philo);
int				eat_sleep_ro_cm(t_philo	*philo);
int				eat_sleep_routi(t_philo	*philo);
int				the_philo_is_dead(t_philo *philo);

#endif
