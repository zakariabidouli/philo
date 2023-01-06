#include "philo.h"
#include <errno.h>

int ft_strlen(char *s)
{
    int i = 0;
    while(s[i])
        i++;
    return (i);
}

void    terminated(char *msg)
{
    printf("%s\n", msg);
    exit(1);
}

// int mynanosleep(long long sec, long nanosec)
// {
//    struct timespec req;
//    req.tv_sec = sec;
//    req.tv_nsec = nanosec;

//    while(req.tv_sec > 0 || req.tv_nsec > 0) 
//    {
//       if( 0 != nanosleep( &req, &req ))
//       {
//           if(errno != EINTR)
//              return -1; 
//       }
//       else
//           break;
//    }         
//    return 0;
// }