/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:47:46 by zbidouli          #+#    #+#             */
/*   Updated: 2023/01/08 00:52:59 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_sem(t_env *env)
{
	int	it;

	it = 0;
	sem_unlink("/print");
	sem_unlink("/forks");
	while (it < env->num_of_philos && env->forks[it] != SEM_FAILED)
	{
		env->forks[it] = sem_open("/forks", O_CREAT, S_IRUSR | S_IWUSR, 1);
		it++;
	}
	env->print = sem_open("/print", O_CREAT, S_IRUSR | S_IWUSR, 1);
	if (env->print == SEM_FAILED || env->forks[it] == SEM_FAILED)
		terminated("SEM_OPEN_ERROR");
}

void	init_philo(t_env	*env, int it)
{
	if (env && it >= 0)
	{
		env->philos[it].id = it + 1;
		env->philos[it].env = env;
		env->philos[it].num_of_eat = 0;
		env->philos[it].last_eat_time = env->start_time;
		env->philos[it].pid = getpid();
		env->philos[it].fork = env->forks[it];
	}
}

void	check_status(t_philo *philo)
{
	long long	time;

	time = get_time() - philo->last_eat_time;
	if (time > philo->env->time_to_die)
	{	
		print_status(philo, "died");
		philo->env->is_dead = true;
	}
	if (philo->num_of_eat == philo->env->num_of_eat)
		stop_simulation(philo->env, philo->env->main_pid);
}

void	print_status(t_philo *philo, char *msg)
{
	long long	time;

	time = get_time() - philo->env->start_time;
	sem_wait(philo->env->print);
	printf("%lld %d %s\n", time, philo->id, msg);
	sem_post(philo->env->print);
	if (philo->env->is_dead == true || str_cmp(msg, "died"))
		stop_simulation(philo->env, philo->env->main_pid);
}
