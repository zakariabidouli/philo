#include "philo.h"
// get_time

// --------
//  get current time
long long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// print_status

// ------------

//  print status of philo
int str_cmp(char *s1, char *s2)
{
    while(*s1 && *s2)
    {
        if(*s1 != *s2)
            return 0;
        s1++;
        s2++;
    }
    return 1;
}

void print_status(t_philo *philo, char *msg)
{
    long long time;

    time = get_time() - philo->env->start_time;
    pthread_mutex_lock(&philo->env->print);
    printf("%lld %d %s\n", time, philo->id + 1, msg);
    if(str_cmp(msg, "DEAD"))
        exit(1);
    pthread_mutex_unlock(&philo->env->print);
}

// check if philo is dead

void    check_status(t_philo *philo)
{
    long long time;

    time = get_time() - philo->last_eat_time;
    if (time > philo->env->time_to_die)
        print_status(philo, "DEAD");
    else if(philo->num_of_eat == philo->env->num_of_eat)
        exit(1);
}

void *routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (philo)
    {
        
        check_status(philo);
        pthread_mutex_lock(philo->mutex);
        print_status(philo, "has taken a fork");

        // printf("#######>>[%d]>>>>>>>>>>>>>\n" , philo->env->is_dead);
        pthread_mutex_lock(philo->mutex + 1);
        print_status(philo, "has taken a fork");

        philo->last_eat_time = get_time();
        print_status(philo, "is eating");
        usleep(philo->env->time_to_eat * 1000);
        philo->num_of_eat++;
        pthread_mutex_unlock(philo->mutex);
        pthread_mutex_unlock(philo->mutex + 1);

        print_status(philo, "is sleeping");
        usleep(philo->env->time_to_sleep * 1000);

        check_status(philo);
        print_status(philo, "is thinking");
        check_status(philo);
    }
    return (philo);
}

int simulate(t_env *env)
{
    int i = 0;
    env->start_time = get_time();
    if(!(env->philos = (t_philo *)malloc(sizeof(t_philo) * env->num_of_philo)))
        terminated("error_malloc");
        
    while (i < env->num_of_philo)
    {
        // printf("init_philo\n");
        env->philos[i].id = i;
        env->philos[i].env = env;
        env->philos[i].num_of_eat = 0;
        env->philos[i].last_eat_time = env->start_time;
        env->philos[i].mutex = &env->forks[i];
        if(pthread_create(&env->philos[i].thread, NULL, routine, &env->philos[i]))
            terminated ("PTHREAD_CREATE_ERROR");
        usleep(600);
        i++;
    }
    i = 0;
    while(i < env->num_of_philo)
    {
        if(pthread_join(env->philos[i].thread, NULL))
            terminated ("PTHREAD_JOIN_ERROR");
        i++;
    }
    // i = 0;
    // while(i < env->num_of_philo)
    // {
    //     if(pthread_detach(env->philos[i].thread))
    //         terminated ("PTHREAD_DETACH_ERROR");
    //     i++;
    // }
    return (0);
}

int main(int ac, char **av)
{
    t_env *env;

    if (ac < 5)
        terminated ("error_missing_args");
    if (ac > 6)
        terminated ("error_many_args");
    if (!(env = (t_env *)malloc(sizeof(t_env))))
        terminated("error_malloc");
    if (parse(ac, av, env))
        terminated("error_parse");
    env->is_dead = false;
    if(simulate(env))
        terminated("error_simulation");
    return (0);
}