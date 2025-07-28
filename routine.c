/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:52:21 by ntahadou          #+#    #+#             */
/*   Updated: 2025/07/28 13:06:55 by ntahadou         ###   ########.fr       */
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

int	is_most_starving(t_philo *philo)
{
	long long	now;
	long long	my_hunger;
	int			i;
	int			most_starving;
	long long	other_hunger;

	now = get_time();
	my_hunger = now - philo->time_last_meal;
	most_starving = 1;
	pthread_mutex_lock(&philo->data->meal_check);
	i = -1;
	while (++i < philo->data->philos_number)
	{
		if (i != philo->id - 1)
		{
			other_hunger = now - philo->data->philos[i].time_last_meal;
			if (other_hunger > my_hunger)
			{
				most_starving = 0;
				break ;
			}
		}
	}
	pthread_mutex_unlock(&philo->data->meal_check);
	return (most_starving);
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
		if (current_time - data->philos[i].time_last_meal > data->time_to_die)
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
