#include "philo.h"

int main(int ac, char **av)
{
    t_data  data;

    if (ac < 5)
    {
        printf("Two many arguments!");
        return (0);
    }
    init_data(&data, av);
    init_philos(&data);
    
    create_philos(&data);
    create_monitor(&data);

    join_philos(&data);
    join_monitor(&data);

    return (0);
}