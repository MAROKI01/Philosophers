#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->meal_check);
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal_check);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!philo->data->someone_died && philo->is_eating)
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	check_dead_philos(t_data *data)
{
	int	current_time;
	int	i;

	i = 0;
	while (i < data->philos_number && !data->someone_died)
	{
		current_time = get_time();
		pthread_mutex_lock(&data->meal_check);
		if (current_time - data->philos[i].time_last_meal > data->time_to_die)
		{
			pthread_mutex_lock(&data->writing);
			printf("=============== %d Philosopher %d has died===========\n",
					current_time - data->philos[i].time_last_meal,
					data->philos[i].id);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->writing);
			pthread_mutex_unlock(&data->meal_check);
			break ;
		}
		pthread_mutex_unlock(&data->meal_check);
		i++;
	}
	return (1);
}

int	is_all_ate(t_data *data)
{
	int	i;
	int	finished_eat;

	finished_eat = 0;
	i = 0;
	while (i < data->philos_number && !data->someone_died)
	{
		pthread_mutex_unlock(&data->meal_check);
		if (data->philos[i].times_eaten >= data->number_of_meals
			&& data->philos[i].is_eating)
		{
			data->philos[i].is_eating = 0;
			finished_eat++;
		}
		pthread_mutex_unlock(&data->meal_check);
		i++;
	}
	pthread_mutex_unlock(&data->meal_check);
	if (finished_eat == data->philos_number)
		data->someone_died = 1;
	pthread_mutex_unlock(&data->meal_check);
	return (1);
}
void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		finished_eat;

	data = (t_data *)arg;
	finished_eat = 0;
	usleep(100000);
	printf("=============== Monitor start ============\n");
	while (!data->someone_died)
	{
		check_dead_philos(data);
        is_all_ate(data);
	}
	return (NULL);
}
