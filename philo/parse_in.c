#include "philo.h"

int get_num(char *s)
{
    int i = 0;
    while (s[i])
    {
        if (s[i] >= '0' || s[i] <= '9')
            i++;
        else
            return(-1);
    }
    return (ft_atoi(s));
}

int parse(int ac, char **av, t_env *env)
{
    if(get_num(av[1]) <= 1 || get_num(av[2]) < 60 || get_num(av[3]) < 60 || get_num(av[4]) < 60)
        terminated ("GRT 1 && 60 && 60 && 60");
    env->num_of_philo = get_num(av[1]);
    env->time_to_die = get_num(av[2]);
    env->time_to_eat = get_num(av[3]);
    env->time_to_sleep = get_num(av[4]);
    if (ac == 6)
        env->num_of_eat = get_num(av[5]);
    else
        env->num_of_eat = -1;
    env->philos = (t_philo *)malloc(sizeof(t_philo) * env->num_of_philo);
    env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * env->num_of_philo);
    // env->print = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
    if (!env->philos || !env->forks)
        return (1);
    pthread_mutex_init(&env->print, NULL);
    int i = 0;
    while (i < env->num_of_philo)
    {
        pthread_mutex_init(&env->forks[i], NULL);
        i++;
    }

    // printf("philos [%p]\n", env->philos);
    // printf("num_of_philo [%ld]\n", env->num_of_philo);
    // printf("time_to_die [%lld]\n", env->time_to_die);
    // printf("time_to_eat [%ld]\n", env->time_to_eat);
    // printf("time_to_sleep [%ld]\n", env->time_to_sleep);
    // printf("num_of_eat [%ld]\n", env->num_of_eat);
    // printf("start->time [%lld]\n", env->start_time);
    // printf("start->is_dead [%d]\n", env->is_dead);

    return (0); 
}

