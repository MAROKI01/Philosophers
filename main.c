/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:51:57 by ntahadou          #+#    #+#             */
/*   Updated: 2025/07/26 14:57:36 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	clean_up(t_data *data)
{
	int	i;

	(void)data;
	i = 0;
	while (i < (data)->philos_number)
	{
		if (pthread_mutex_destroy(&(data)->forks[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_destroy(&data->writing) != 0
		|| pthread_mutex_destroy(&data->meal_check) != 0
		|| pthread_mutex_destroy(&data->death) != 0)
		return (-1);
	if (data)
	{
		if (data->philos)
			free(data->philos);
		if (data->forks)
			free(data->forks);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5)
	{
		printf("Two few arguments!");
		return (0);
	}
	if (check_argemunt(av) == 1)
		return (2);
	if (init(&data, av) == -1)
	{
		clean_up(&data);
		return (2);
	}
	if (create_threads(&data) == -1)
	{
		clean_up(&data);
		return (2);
	}
	clean_up(&data);
	return (0);
}
