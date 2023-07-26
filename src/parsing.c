/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 12:19:27 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/26 14:18:41 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
