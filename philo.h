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

typedef struct s_data t_data; // Forward declaration

typedef struct s_philo
{
	int				id;
	int				time_last_meal;
	int				times_eaten;
	int				has_two_forks;
	pthread_t		routine;
	t_data *data;   // Add pointer to shared data
	int left_fork;  // Index of left fork
	int right_fork; // Index of right fork
}					t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				someone_died;
	int				philos_number;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	*forks;
	pthread_mutex_t writing; // Add mutex for console output
	pthread_mutex_t meal_check; // Add mutex for console output
	long long start_time;    // Add program start time
	pthread_t		monitor;
}					t_data;

long				ft_atoi(const char *str);
int					ft_isdigit(char c);
int					is_number(char *str);

int					init_philos(t_data *data);
int					init_data(t_data *data, char **av);

int					create_philos(t_data *data);
int					join_philos(t_data *data);
int					create_monitor(t_data *data);
int					join_monitor(t_data *data);

void				*philo_routine(void *);
void				*monitor_routine(void *);

void				eating(t_philo *philo);
void				sleeping(t_philo *philo);
void				thinking(t_philo *philo);

long long get_time(void);

#endif