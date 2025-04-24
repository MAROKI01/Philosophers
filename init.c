#include "philo.h"

int	init_philos(t_data *data)
{
	int	i;

	(data)->philos = malloc(sizeof(t_philo) * (data)->philos_number);
	i = 0;
	while (i < (data)->philos_number)
	{
		memset(&data->philos[i], 0, sizeof(t_philo));
		data->philos[i].id = i + 1;
		data->philos[i].data = data;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->philos_number;
		i++;
	}
	
	return (0);
}

int	init_data(t_data *data, char **av)
{
	int i;

	i = 1;
	memset(data, 0, sizeof(t_data));
	while (i < 5)
	{
		if (!is_number(av[i]))
			return (0);
		i++;
	}
	(data)->philos_number = ft_atoi(av[1]);
	(data)->time_to_die = ft_atoi(av[2]);
	(data)->time_to_eat = ft_atoi(av[3]);
	(data)->time_to_sleep = ft_atoi(av[4]);
	(data)->someone_died = 0;
	(data)->start_time = get_time();
	(data)->forks = malloc(sizeof(pthread_mutex_t) * (data)->philos_number);
	for (int i = 0; i < (data)->philos_number; i++)
	{
		pthread_mutex_init(&(data)->forks[i], NULL);
	}
	return (1);
}