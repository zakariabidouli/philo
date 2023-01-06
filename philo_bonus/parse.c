#include "philo_bonus.h"

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
    int it;

    if(get_num(av[1]) <= 1 || get_num(av[2]) < 60
        || get_num(av[3]) < 60 || get_num(av[4]) < 60)
        terminated ("GRT 1 && 60 && 60 && 60");
    env->num_of_philos = get_num(av[1]);
    env->time_to_die = get_num(av[2]);
    env->time_to_eat  = get_num(av[3]);
    env->time_to_sleep  = get_num(av[4]);
    if(ac == 6)
        env->num_of_eat = get_num(av[5]);
    else
        env->num_of_eat = -1;
    env->is_dead = false;
    env->eat_count = 0;
    env->main_pid = getpid();
    env->philos = (t_philo *)malloc(sizeof(t_philo *) * env->num_of_philos);
    env->forks = (sem_t **)malloc(sizeof(sem_t *) * env->num_of_philos);
    if(!env->philos)
        terminated("ERROR_MC");
    env->is_dead = false;
    init_sem(env);
    return 0;
}