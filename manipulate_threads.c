/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_threads.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:52:02 by ntahadou          #+#    #+#             */
/*   Updated: 2025/07/26 14:52:06 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data)->philos_number)
	{
		if (pthread_create(&(data)->philos[i].routine, NULL, &philo_routine,
				(data->philos + i)) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	join_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data)->philos_number)
	{
		if (pthread_join((data)->philos[i].routine, NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	if (create_philos(data) == -1)
		return (-1);
	monitor_routine(data);
	if (join_philos(data) == -1)
		return (-1);
	return (0);
}
