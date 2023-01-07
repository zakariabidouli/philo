/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbidouli <zbidouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/07 00:29:00 by zbidouli          #+#    #+#             */
/*   Updated: 2023/01/07 00:31:40 by zbidouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	str_len(char *str)
{
	int	it;

	it = 0;
	while (str[it])
		it++;
	return (it);
}

void	put_str(char *msg)
{
	printf("[%s]\n", msg);
}

void	terminated(char *msg)
{
	put_str(msg);
	exit(1);
}

int	fork_protected(void)
{
	int	pid;

	pid = fork();
	if (pid < -1)
		terminated("FORK_ERROR");
	return (pid);
}

int	str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}
