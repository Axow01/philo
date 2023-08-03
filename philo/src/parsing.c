/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:19:27 by mmarcott          #+#    #+#             */
/*   Updated: 2023/08/03 14:58:56 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_unlock_eat_mutex(t_philo *philo)
{
	change_status_fork(philo, 0);
	pthread_mutex_unlock(philo->fork_right);
	pthread_mutex_unlock(philo->fork_left);
}

void	ft_norm(t_philo *philo)
{
	while (!is_death(philo) 
		&& !ft_check_forks(philo, philo->sim->fork_status))
		usleep(200);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i++])
		;
	return (i);
}

static bool	ft_isdigit_str(const char **args, int8_t count)
{
	int8_t	i;
	int8_t	k;

	k = 0;
	while (++k < count)
	{
		i = -1;
		while (args[k][++i])
			if (!(args[k][i] >= '0' && args[k][i] <= '9'))
				return (false);
	}
	return (true);
}

bool	ft_parsing(t_simulation *sim, const char **args, int8_t argc)
{
	if (!ft_isdigit_str(args, argc))
		return (false);
	sim->nb_philo = ft_atoi(args[1]);
	sim->t_die = ft_atoi(args[2]);
	sim->t_eat = ft_atoi(args[3]);
	sim->t_sleep = ft_atoi(args[4]);
	sim->nb_each_eat = 0;
	if (argc == 6)
		sim->nb_each_eat = ft_atoi(args[5]);
	return (true);
}
