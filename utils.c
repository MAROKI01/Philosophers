#include "philo.h"

long long get_time(void)
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void eating(t_philo *philo)
{
    // take the left fork
    pthread_mutex_lock(&(philo->data->forks[philo->left_fork]));
    pthread_mutex_lock(&(philo->data->writing));
    if (!philo->data->someone_died)
        printf("%lld Philosopher %d has taken a fork(left)\n", get_time() - philo->data->start_time, philo->id);
    pthread_mutex_unlock(&philo->data->writing);
    // take the right fork
    pthread_mutex_lock(&(philo->data->forks[philo->right_fork]));
    pthread_mutex_lock(&philo->data->writing);
    if (!philo->data->someone_died)
        printf("%lld Philosopher %d has taken a fork(right)\n", get_time() - philo->data->start_time, philo->id);
    pthread_mutex_unlock(&philo->data->writing);
    // eat
    pthread_mutex_lock(&philo->data->writing);
    if (!philo->data->someone_died)
        printf("%lld Philosopher %d is eating\n", get_time() - philo->data->start_time, philo->id);
    pthread_mutex_unlock(&philo->data->writing);
    // Update meal time with mutex protection
    pthread_mutex_lock(&philo->data->meal_check);
    philo->time_last_meal = get_time();
    philo->times_eaten++;
    pthread_mutex_unlock(&philo->data->meal_check);
    
    // Convert milliseconds to microseconds
    usleep(philo->data->time_to_eat * 1000);
    // to put down the forks
    pthread_mutex_unlock(&(philo->data->forks[philo->left_fork]));
    printf("Philosopher %d put down the left fork\n", philo->id);
    pthread_mutex_unlock(&(philo->data->forks[philo->right_fork]));
    printf("Philosopher %d put down the right fork\n", philo->id);
}

void sleeping(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->writing);
    if (!philo->data->someone_died)
        printf("%lld Philosopher %d is sleeping\n", get_time() - philo->data->start_time, philo->id);
    pthread_mutex_unlock(&philo->data->writing);
    usleep(philo->data->time_to_sleep * 1000);
    
}

void thinking(t_philo *philo)
{
    pthread_mutex_lock(&philo->data->writing);
    if (!philo->data->someone_died)
        printf("%lld Philosopher %d is thinking\n", get_time() - philo->data->start_time , philo->id);
    pthread_mutex_unlock(&philo->data->writing);
    usleep(1000); // Sleep for a short time to simulate thinking
}
