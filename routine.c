/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:52:21 by ntahadou          #+#    #+#             */
/*   Updated: 2025/07/26 15:24:17 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_someone_dead(t_data *data)
{
	pthread_mutex_lock(&data->death);
	if (data->someone_died)
	{
		pthread_mutex_unlock(&data->death);
		return (1);
	}
	pthread_mutex_unlock(&data->death);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0
		&& philo->data->philos_number == 3)
		ft_usleep(1);
	while (!is_someone_dead(philo->data))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	check_dead_philos(t_data *data)
{
	long long	current_time;
	int			i;

	i = -1;
	while (++i < data->philos_number)
	{
		pthread_mutex_lock(&data->meal_check);
		current_time = get_time();
		if (current_time - data->philos[i].time_last_meal > data->time_to_die
			&& !data->philos[i].is_eating)
		{
			pthread_mutex_lock(&data->writing);
			printf("%lld %d has died\n",
				current_time - data->start_time,
				data->philos[i].id);
			pthread_mutex_unlock(&data->writing);
			pthread_mutex_lock(&data->death);
			data->someone_died = 1;
			pthread_mutex_unlock(&data->death);
			pthread_mutex_unlock(&data->meal_check);
			return (1);
		}
		pthread_mutex_unlock(&data->meal_check);
	}
	return (0);
}

int	is_all_ate(t_data *data)
{
	int	i;
	int	finished_eat;

	finished_eat = 0;
	i = -1;
	pthread_mutex_lock(&data->meal_check);
	while (++i < data->philos_number)
	{
		if (data->philos[i].times_eaten >= data->number_of_meals
			&& data->number_of_meals > 0)
			finished_eat++;
	}
	pthread_mutex_unlock(&data->meal_check);
	if (finished_eat == data->philos_number)
	{
		pthread_mutex_lock(&data->death);
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death);
		pthread_mutex_lock(&data->writing);
		printf("All philosophers have eaten %d times\n", data->number_of_meals);
		pthread_mutex_unlock(&data->writing);
		return (1);
	}
	return (0);
}

void	monitor_routine(t_data *data)
{
	while (!data->someone_died)
	{
		if (is_all_ate(data) == 1)
			break ;
		if (check_dead_philos(data) == 1)
			break ;
	}
}
