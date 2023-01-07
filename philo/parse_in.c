/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:00:29 by zbidouli          #+#    #+#             */
/*   Updated: 2023/01/07 00:26:48 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_num(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] >= '0' || s[i] <= '9')
			i++;
		else
			return (-1);
	}
	return (ft_atoi(s));
}

void	init_mut(t_env *env)
{
	int	i;

	i = 0;
	pthread_mutex_init(&env->print, NULL);
	while (i < env->num_of_philo)
	{
		pthread_mutex_init(&env->forks[i], NULL);
		i++;
	}
}

int	parse(int ac, char **av, t_env *env)
{
	if (get_num(av[1]) <= 1 || get_num(av[2]) < 60
		|| get_num(av[3]) < 60 || get_num(av[4]) < 60)
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
	env->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* env->num_of_philo);
	if (!env->philos || !env->forks)
		return (1);
	init_mut(env);
	return (0);
}
