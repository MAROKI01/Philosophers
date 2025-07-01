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

// int	create_monitor(t_data *data)
// {
// 	if (pthread_create(&(data)->monitor, NULL, &monitor_routine, data) != 0)
// 		return (-1);
// 	return (0);
// }

// int	join_monitor(t_data *data)
// {
// 	if (pthread_join((data)->monitor, NULL) != 0)
// 		return (-1);
// 	return (0);
// }

int	create_threads(t_data *data)
{
	if (create_philos(data) == -1)
		return (-1);
	monitor_routine(data);
	if (join_philos(data) == -1)
		return (-1);
	return (0);
}