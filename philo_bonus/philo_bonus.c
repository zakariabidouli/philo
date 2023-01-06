#include "philo_bonus.h"

long long get_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void    check_status(t_philo *philo)
{
    long long time;

    time = get_time() - philo->last_eat_time;
    if (time > philo->env->time_to_die)
        philo->env->is_dead = true;
    else if(philo->num_of_eat == philo->env->num_of_eat)
        philo->env->is_dead = true;
}

void print_status(t_philo *philo, char *msg)
{
    long long time;

    time = get_time() - philo->env->start_time;
    sem_wait(philo->env->print);
    printf("%lld %d %s\n", time, philo->id, msg);
    sem_post(philo->env->print);
    if(philo->env->is_dead == true)
        stop_simulation(philo->env, philo->env->main_pid);
  
}


void    *routine(void    *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    while (1)
    {
        check_status(philo);
        sem_wait(philo->fork);
        print_status(philo, "picked up L fork");
        sem_wait(&philo->fork[philo->id + 1]);
        print_status(philo, "picked up R fork");

        print_status(philo, "is eating");
        usleep(philo->env->time_to_eat * 1000);
        philo->num_of_eat++;
        philo->last_eat_time = get_time();

        sem_post(philo->fork);
        sem_post(&philo->fork[philo->id + 1]);
        // check_status(philo);
        print_status(philo, "is sleeping");
        usleep(philo->env->time_to_sleep * 1000);
        print_status(philo, "is thinking");
    }
}

void    stop_simulation(t_env *env, int exit)
{
    int it = 0;
    pid_t pid;

    while(it < env->num_of_philos)
    {
        sem_close(env->forks[it]);
        it++;
    }
    sem_close(env->print);
	sem_unlink("/print");
	sem_unlink("/forks");
    kill(0, SIGKILL);
    
    // it = 0;
    // while(it < env->num_of_philos)
    // {
    //     it++;
    // }
    // free(env);
    // exit(1);
}

void    sup(t_philo *philo)
{
    if(pthread_join(philo->thread, NULL))
        terminated("JOIN_ERROR");
}

void init_sem(t_env *env)
{
    int it;

	sem_unlink("/print");
    sem_unlink("/forks");
    while(it < env->num_of_philos && env->forks[it] != SEM_FAILED)
    {
        // env->forks[it] = (sem_t *)malloc(sizeof(sem_t *));
        env->forks[it] = sem_open("/forks", O_CREAT , S_IRUSR | S_IWUSR, 1);
        it++;
    }
    env->print = sem_open("/print", O_CREAT , S_IRUSR | S_IWUSR, 1);
    if (env->print == SEM_FAILED || env->forks[it] == SEM_FAILED)
		terminated("SEM_OPEN_ERROR");
}

int simulate(t_env  *env)
{
    int it;
    pid_t   status;

    if(!(env->philos = (t_philo *)malloc(sizeof(t_philo) * env->num_of_philos)))
        terminated("error_malloc");
    env->start_time = get_time();
    it = 0;
    while(it < env->num_of_philos)
    {
        if(fork_protected() == 0)
        {
            env->philos[it].id = it + 1; 
            env->philos[it].env = env;
            env->philos[it].num_of_eat = 0;
            env->philos[it].last_eat_time = env->start_time;
            env->philos[it].pid = getpid();
            // printf("\nid>> [%d] pid>> [%d]\n",env->philos[it].id, env->philos[it].pid);
            // printf("\nid>> main pid>> [%d]\n",env->main_pid);
            env->philos[it].fork = env->forks[it];
            if(pthread_create(&env->philos[it].thread, NULL, routine, &env->philos[it]))
                return 1;
            usleep(600);
            sup(&env->philos[it]);
        }
        it++;
    }
    waitpid(-1, &status, 0);
    if(status != 0)
        stop_simulation(env, env->main_pid);
    return 0;
}

void test(int ac, char **av)
{
    t_env *env;

    if(!(env = (t_env *)malloc(sizeof(t_env))))
        terminated("Error_malloc");
    // printf("main pid = %d\n", env);
    if(ac < 5)
        terminated("TOO_FEW_ARGS");
    if(ac > 6)
        terminated("TOO_MANY_ARGS");
    if(ac == 5 || ac == 6)
    {
        if(parse(ac, av, env))
            terminated("Error_parse");
        if(simulate(env))
            terminated("Error_simulate");
        // stop_simulation(env , env->main_pid);
    }
    return ;           
}

int main(int ac, char **av)
{
    test(ac, av);
    system("leaks philo_bonus");
 

}