/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:52:14 by ntahadou          #+#    #+#             */
/*   Updated: 2025/07/28 12:42:00 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&(philo->data->forks[philo->left_fork]));
		pthread_mutex_lock(&(philo->data->forks[philo->right_fork]));
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[philo->right_fork]));
		pthread_mutex_lock(&(philo->data->forks[philo->left_fork]));
		print_message(philo, "has taken a fork");
	}
}

void	eating(t_philo *philo)
{
	if (philo->data->philos_number == 1)
	{
		pthread_mutex_lock(&(philo->data->forks[philo->left_fork]));
		print_message(philo, "has taken a fork");
		ft_usleep(philo->data->time_to_die);
		pthread_mutex_unlock(&(philo->data->forks[philo->left_fork]));
		return ;
	}
	take_forks(philo);
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_check);
	philo->times_eaten++;
	philo->time_last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal_check);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&(philo->data->forks[philo->right_fork]));
	pthread_mutex_unlock(&(philo->data->forks[philo->left_fork]));
}

void	sleeping(t_philo *philo)
{
	print_message(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

void	thinking(t_philo *philo)
{
	print_message(philo, "is thinking");
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!is_someone_dead(philo->data))
	{
		thinking(philo);
		if (is_most_starving(philo))
			eating(philo);
		sleeping(philo);
	}
	return (NULL);
}
