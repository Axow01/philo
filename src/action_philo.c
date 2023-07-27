/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:22:58 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/27 19:18:39 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	philo_eat(t_philo *philo)
{
	time_t	eating;
	bool	dead;
	int		id;

	pthread_mutex_lock(&philo->sim->fork[philo->id]);
	print_p("has taken a fork", philo);
	id = philo->id - 1;
	if (philo->id == 0)
		id = philo->sim->nb_philo - philo->id - 1;
	pthread_mutex_lock(&philo->sim->fork[id]);
	print_p("has taken a fork", philo);
	dead = print_p("is eating", philo);
	pthread_mutex_lock(&philo->sim->eat);
	philo->death_time = get_time() + philo->sim->t_die;
	philo->time_eaten += 1;
	eating = get_time() + philo->sim->t_eat;
	pthread_mutex_unlock(&philo->sim->eat);
	while (get_time() < eating)
		;
	pthread_mutex_unlock(&philo->sim->fork[id]);
	pthread_mutex_unlock(&philo->sim->fork[philo->id]);
	if (philo->time_eaten >= philo->sim->nb_each_eat && philo->sim->nb_each_eat > 0)
		return (false);
	return (dead);
}
