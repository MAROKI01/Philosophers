#include "philo.h"

void *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;    
    pthread_mutex_lock(&philo->data->meal_check);
    philo->time_last_meal = get_time();
    pthread_mutex_unlock(&philo->data->meal_check);
    
    if (philo->id % 2 == 0)
        usleep(10000);
    while(1)
    {
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
    return (NULL);
}

void *monitor_routine(void *arg)
{
    t_data *data;
    int current_time;
    int i;

    data = (t_data *)arg;
    
    usleep(1000000); 

    while (!data->someone_died)
    {
        i = 0;
        while (i < data->philos_number && !data->someone_died)
        {
            current_time = get_time();
            
            pthread_mutex_lock(&data->meal_check);
            if (current_time - data->philos[i].time_last_meal > data->time_to_die)
            {
                pthread_mutex_lock(&data->writing);
                printf("Philosopher %d has died\n", data->philos[i].id);
                data->someone_died = 1;
                pthread_mutex_unlock(&data->writing);
                pthread_mutex_unlock(&data->meal_check);
                exit(0);
            }
            pthread_mutex_unlock(&data->meal_check);
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}