/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:01:09 by zbidouli          #+#    #+#             */
/*   Updated: 2023/01/08 23:47:02 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, char *msg)
{
	long long	time;

	time = get_time() - philo->env->start_time;
	pthread_mutex_lock(&philo->env->print);
	printf("%lld %d %s\n", time, philo->id + 1, msg);
	if (str_cmp(msg, "died"))
		exit(1);
	pthread_mutex_unlock(&philo->env->print);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo)
	{
		check_status(philo);
		pthread_mutex_lock(philo->mutex);
		print_status(philo, "has taken a fork");
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
		usleep(1);
	}
	return (philo);
}

void	sup(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->num_of_philo)
	{
		if (pthread_join(env->philos[i].thread, NULL))
			terminated ("PTHREAD_JOIN_ERROR");
		if (pthread_detach(env->philos[i].thread))
			terminated ("PTHREAD_DETACH_ERROR");
		i++;
	}
}

int	simulate(t_env *env)
{
	int	i;

	i = 0;
	env->start_time = get_time();
	while (i < env->num_of_philo)
	{
		env->philos[i].id = i;
		env->philos[i].env = env;
		env->philos[i].num_of_eat = 0;
		env->philos[i].last_eat_time = env->start_time;
		env->philos[i].mutex = &env->forks[i];
		if (pthread_create(&env->philos[i].thread, NULL,
				routine, &env->philos[i]))
			terminated ("PTHREAD_CREATE_ERROR");
		usleep(600);
		i++;
	}
	sup(env);
	return (0);
}

int	main(int ac, char **av)
{
	t_env	*env;

	if (ac < 5)
		terminated ("error_missing_args");
	if (ac > 6)
		terminated ("error_many_args");
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		terminated("error_malloc");
	if (parse(ac, av, env))
		terminated("error_parse");
	env->is_dead = false;
	if (simulate(env))
		terminated("error_simulation");
	return (0);
}
