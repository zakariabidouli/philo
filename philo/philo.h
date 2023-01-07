/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:16:29 by zbidouli          #+#    #+#             */
/*   Updated: 2023/01/07 00:22:16 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef enum s_bool
{
	false,
	true,
}	t_bool;

typedef struct s_philo
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	*mutex;
	struct s_env	*env;
	long			dead_time;
	long			last_eat_time;
	long			num_of_eat;
	char			*stat;
}	t_philo;

typedef struct s_env
{
	struct s_philo	*philos;
	t_bool			is_dead;
	long long		start_time;
	long			num_of_philo;
	long long		time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			eat_count;
	long			num_of_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}	t_env;

int			ft_atoi(const char	*str);
int			parse(int ac, char **av, t_env *env);
void		check_status(t_philo *philo);
int			str_cmp(char *s1, char *s2);
void		terminated(char *msg);
long long	get_time(void);
int			get_num(char *s);
void		print_status(t_philo *philo, char *msg);

#endif