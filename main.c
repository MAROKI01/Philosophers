#include "philo.h"

int main(int ac, char **av)
{
    t_data  data;

    if (ac < 5)
    {
        printf("Two many arguments!");
        return (0);
    }
    if (check_argemunt(av) == 1)
        return (1);
    init(&data, av);
    create_threads(&data);
    return (0);
}