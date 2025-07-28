/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:52:08 by ntahadou          #+#    #+#             */
/*   Updated: 2025/07/28 18:34:58 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

typedef struct s_data	t_data;

typedef struct s_philo
{
	int					id;
	long long			time_last_meal;
	int					times_eaten;
	int					has_two_forks;
	pthread_t			routine;
	t_data				*data;
	int					left_fork;
	int					right_fork;
	int					is_eating;
	int					must_eat_first;
}						t_philo;

typedef struct s_data
{
	t_philo				*philos;
	int					someone_died;
	int					philos_number;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_meals;
	pthread_mutex_t		*forks;
	pthread_mutex_t		writing;
	pthread_mutex_t		meal_check;
	pthread_mutex_t		death;
	long long			start_time;
	pthread_t			monitor;
}						t_data;

long					ft_atoi(const char *str);
int						ft_isdigit(char c);
int						is_number(char *str);

int						init(t_data *data, char **av);

int						create_philos(t_data *data);
int						join_philos(t_data *data);
int						is_most_starving(t_philo *philo);
int						is_starving(t_philo *philo);
int						create_threads(t_data *data);
int						is_someone_dead(t_data *data);

void					*philo_routine(void *arg);
void					monitor_routine(t_data *data);

void					eating(t_philo *philo);
void					sleeping(t_philo *philo);
void					thinking(t_philo *philo);

long long				get_time(void);
void					print_message(t_philo *philo, char *msg);
int						is_someone_dead(t_data *data);
int						check_argemunt(char **av);
int						ft_usleep(long long milliseconds);

#endif