/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:54:16 by zbidouli          #+#    #+#             */
/*   Updated: 2023/01/07 00:57:13 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/time.h>

typedef enum s_bool
{
	false,
	true,
}	t_bool;

typedef struct s_philos
{
	int				id;
	pthread_t		thread;
	pid_t			pid;
	struct s_env	*env;
	sem_t			*fork;
	long			dead_time;
	long			last_eat_time;
	long			num_of_eat;
}	t_philo;

typedef struct s_env
{
	t_philo		*philos;
	t_bool		is_dead;
	pid_t		main_pid;
	long long	start_time;
	int			num_of_philos;
	long long	time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		eat_count;
	long		num_of_eat;
	sem_t		**forks;
	sem_t		*print;
}	t_env;

int			parse(int ac, char **av, t_env *env);
int			ft_atoi(const char	*str);
void		terminated(char *msg);
int			str_cmp(char *s1, char *s2);
int			fork_protected(void);
void		print_status(t_philo *philo, char *msg);
void		check_status(t_philo *philo);
void		stop_simulation(t_env *env, int exit);
void		init_philo(t_env	*env, int it);
void		init_sem(t_env *env);
void		ft_usleep(int ms);
long long	get_time(void);

#endif
