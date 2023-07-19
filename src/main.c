/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:10:13 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/19 18:23:14 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	if (!(argc == 5) && !(argc == 6))
	{
		printf("Error\nUsage: ./philo nbphilo tdie teat tsleep [nb_t_philo_eat]\n"
			);
		return (1);
	}
	(void)argv;
	return (0);
}
