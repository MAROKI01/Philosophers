#include "philo.h"

void eating(t_philo *philo)
{
    pthread_mutex_lock(&(philo->data->forks[philo->right_fork]));
    print_message(philo, "has taken a fork");

    pthread_mutex_lock(&(philo->data->forks[philo->left_fork]));
    print_message(philo, "has taken a fork");

    print_message(philo, "is eating");

    pthread_mutex_lock(&philo->data->meal_check);
    philo->time_last_meal = get_time();
    philo->times_eaten++;
    pthread_mutex_unlock(&philo->data->meal_check);

    usleep(philo->data->time_to_eat * 1000);

    pthread_mutex_unlock(&(philo->data->forks[philo->right_fork]));
    pthread_mutex_unlock(&(philo->data->forks[philo->left_fork]));
}

void sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->writing);
    if (!philo->data->someone_died)
        printf("%lld  %d is sleeping\n", get_time() - philo->data->start_time, philo->id);
    pthread_mutex_unlock(&philo->data->writing);
    usleep(philo->data->time_to_sleep * 1000);
}

void thinking(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->writing);
    if (!philo->data->someone_died)
        printf("%lld  %d is thinking\n", get_time() - philo->data->start_time , philo->id);
    pthread_mutex_unlock(&philo->data->writing);
}
