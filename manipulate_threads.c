#include "philo.h"

int	create_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < (data)->philos_number)
	{
		pthread_create(&(data)->philos[i].routine, NULL, &philo_routine,
				(data->philos + i));
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
		pthread_join((data)->philos[i].routine, NULL);
		i++;
	}
	return (0);
}

int	create_monitor(t_data *data)
{
	pthread_create(&(data)->monitor, NULL, &monitor_routine, NULL);
	return (0);
}

int	join_monitor(t_data *data)
{
	pthread_join((data)->monitor, NULL);
	return (0);
}