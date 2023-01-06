#include "philo_bonus.h"

int str_len(char *str) 
{
    int it;

    it = 0;
    while(str[it])
        it++;
    return it;
}

void put_str(char *msg)
{
    printf("[%s]\n", msg);
}

void terminated(char *msg)
{
    put_str(msg);
    exit(1);
}

int    fork_protected()
{
    int pid;

    pid  =  fork();
    if(pid < -1)
        terminated("FORK_ERROR");
    return pid;
}

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


// void	ft_usleep(int ms)
// {
// 	long	time;

// 	time = get_time();
// 	usleep(ms * 1000);
// 	while (get_time() < time + ms)
// 		usleep(ms * 3);
// }
