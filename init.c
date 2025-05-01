#include "philo.h"

int	init_philos(t_data *data)
{
	int	i;

	(data)->philos = malloc(sizeof(t_philo) * (data)->philos_number);
	if (!(data)->philos)
		return (-1);
	i = 0;
	while (i < (data)->philos_number)
	{
		memset(&data->philos[i], 0, sizeof(t_philo));
		data->philos[i].id = i + 1;
		data->philos[i].is_eating = 1;
		data->philos[i].data = data;
		data->philos[i].left_fork = i;
		if (i == 0)
			data->philos[i].right_fork = data->philos_number - 1;
		else 
			data->philos[i].right_fork = i - 1;
		i++;
	}
	return (0);
}

int	init_data(t_data *data, char **av)
{
	int i;

	memset(data, 0, sizeof(t_data));
	(data)->philos_number = ft_atoi(av[1]);
	(data)->time_to_die = ft_atoi(av[2]);
	(data)->time_to_eat = ft_atoi(av[3]);
	(data)->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		(data)->number_of_meals = ft_atoi(av[5]);
	(data)->someone_died = 0;
	(data)->start_time = get_time();
	(data)->forks = malloc(sizeof(pthread_mutex_t) * (data)->philos_number);
	if (!(data)->forks)
		return(-1);
	i = 0;
	while (i < (data)->philos_number)
	{
		if (pthread_mutex_init(&(data)->forks[i], NULL) != 0)
			return (-1);
		i++;
	}
	return (0);
}

int init(t_data *data, char **av)
{
	if (init_data(data, av) == -1)
		return (-1);
	if (init_philos(data) == -1)
		return (-1);
	return (0);
}