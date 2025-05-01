#include "philo.h"

int	ft_isdigit(char c)
{
	return (c <= '9' && c >= '0');
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long long get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void print_message(t_philo *philo,char *msg)
{
    pthread_mutex_lock(&philo->data->writing);
    if (!philo->data->someone_died)
        printf("%lld  %d %s\n", get_time() - philo->data->start_time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->writing);
}

int check_argemunt(char **av)
{
    if (ft_atoi(av[1]) < 1 || !is_number(av[1]) || ft_atoi(av[1]) > INT_MAX)
        return(printf("Enter a valid philo number"), 1);
    if (ft_atoi(av[2]) < 1 || !is_number(av[2]) || ft_atoi(av[2]) > INT_MAX)
        return(printf("Enter a valid time to die number"), 1);
    if (ft_atoi(av[3]) < 1 || !is_number(av[3]) || ft_atoi(av[3]) > INT_MAX)
        return(printf("Enter a valid time to eat number"), 1);
    if (ft_atoi(av[4]) < 1 || !is_number(av[4]) || ft_atoi(av[4]) > INT_MAX)
        return(printf("Enter a valid time to sleep number"), 1);
    if (av[5] && (ft_atoi(av[5]) < 1 || !is_number(av[5]) || ft_atoi(av[5]) > INT_MAX))
        return (printf("Enter a valid times to eat number"), 1);
    return (0);
}