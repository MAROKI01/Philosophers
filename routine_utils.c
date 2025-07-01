#include "philo.h"

void eating(t_philo *philo)
{
    pthread_mutex_lock(&(philo->data->forks[philo->right_fork]));
    print_message(philo, "has taken a fork");
    if (philo->data->philos_number == 1)
	{
        ft_usleep(philo->data->time_to_die);
        pthread_mutex_unlock(&(philo->data->forks[philo->right_fork]));
        return;
	}
    pthread_mutex_lock(&(philo->data->forks[philo->left_fork]));
    print_message(philo, "has taken a fork");

    print_message(philo, "is eating");

    philo->is_eating = 1;
    pthread_mutex_lock(&philo->data->meal_check);
    philo->time_last_meal = get_time();
    philo->times_eaten++;
    pthread_mutex_unlock(&philo->data->meal_check);
    ft_usleep(philo->data->time_to_eat);
    philo->is_eating = 0;

    pthread_mutex_unlock(&(philo->data->forks[philo->right_fork]));
    pthread_mutex_unlock(&(philo->data->forks[philo->left_fork]));
}

void sleeping(t_philo *philo)
{
    print_message(philo, "is sleeping");
    ft_usleep(philo->data->time_to_sleep);
}

void thinking(t_philo *philo)
{
    print_message(philo, "is thinking");
}
