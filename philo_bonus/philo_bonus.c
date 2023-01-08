/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:28:39 by zbidouli          #+#    #+#             */
/*   Updated: 2023/01/08 23:28:25 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		check_status(philo);
		sem_wait(philo->fork);
		print_status(philo, "has taken a fork");
		sem_wait(&philo->fork[philo->id + 1]);
		print_status(philo, "has taken a fork");
		philo->last_eat_time = get_time();
		print_status(philo, "is eating");
		usleep(philo->env->time_to_eat * 1005);
		philo->num_of_eat++;
		sem_post(philo->fork);
		sem_post(&philo->fork[philo->id + 1]);
		print_status(philo, "is sleeping");
		usleep(philo->env->time_to_sleep * 1005);
		print_status(philo, "is thinking");
	}
}

void	stop_simulation(t_env *env, int exit)
{
	int		it;

	it = 0;
	while (it < env->num_of_philos)
	{
		sem_close(env->forks[it]);
		it++;
	}
	sem_close(env->print);
	sem_unlink("/print");
	sem_unlink("/forks");
	pthread_detach(env->philos[it].thread);
	kill(0, SIGKILL);
}

void	sup(t_philo *philo)
{
	if (pthread_join(philo->thread, NULL))
		terminated("JOIN_ERROR");
}

int	simulate(t_env *env)
{
	int		it;
	pid_t	status;

	env->philos = (t_philo *)malloc(sizeof(t_philo) * env->num_of_philos);
	if (!env->philos)
		terminated("error_malloc");
	env->start_time = get_time();
	it = 0;
	while (it < env->num_of_philos)
	{
		if (fork_protected() == 0)
		{
			init_philo(env, it);
			if (pthread_create(&env->philos[it].thread, NULL,
					routine, &env->philos[it]))
				return (1);
			usleep(1000);
			sup(&env->philos[it]);
		}
		it++;
	}
	waitpid(-1, &status, 0);
	if (status != 0)
		stop_simulation(env, env->main_pid);
	return (0);
}

int	main(int ac, char **av)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		terminated("Error_malloc");
	if (ac < 5)
		terminated("TOO_FEW_ARGS");
	if (ac > 6)
		terminated("TOO_MANY_ARGS");
	if (ac == 5 || ac == 6)
	{
		if (parse(ac, av, env))
			terminated("Error_parse");
		if (simulate(env))
			terminated("Error_simulate");
	}
	return (0);
}
