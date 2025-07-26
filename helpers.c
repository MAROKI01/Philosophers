/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahadou <ntahadou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 14:51:37 by ntahadou          #+#    #+#             */
/*   Updated: 2025/07/26 15:26:30 by ntahadou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	print_message(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->writing);
	if (!is_someone_dead(philo->data))
		printf("%lld %d %s\n", get_time() - philo->data->start_time, philo->id,
			msg);
	pthread_mutex_unlock(&philo->data->writing);
}

int	check_argemunt(char **av)
{
	if (!is_number(av[1]) || ft_atoi(av[1]) < 1 || ft_atoi(av[1]) > INT_MAX)
		return (printf("Enter a valid philo number"), 1);
	if (!is_number(av[2]) || ft_atoi(av[2]) < 1 || ft_atoi(av[2]) > INT_MAX)
		return (printf("Enter a valid time to die number"), 1);
	if (!is_number(av[3]) || ft_atoi(av[3]) < 1 || ft_atoi(av[3]) > INT_MAX)
		return (printf("Enter a valid time to eat number"), 1);
	if (!is_number(av[4]) || ft_atoi(av[4]) < 1 || ft_atoi(av[4]) > INT_MAX)
		return (printf("Enter a valid time to sleep number"), 1);
	if (av[5] && (!is_number(av[5]) || ft_atoi(av[5]) < 1
			|| ft_atoi(av[5]) > INT_MAX))
		return (printf("Enter a valid times to eat number"), 1);
	return (0);
}

int	ft_usleep(long long milliseconds)
{
	long long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < milliseconds)
	{
		usleep(500);
	}
	return (0);
}
