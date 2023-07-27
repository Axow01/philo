/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:22:58 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/27 15:02:21 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	philo_eat(t_philo *philo)
{
	time_t	eating;
	bool	dead;

	pthread_mutex_lock(&philo->sim->fork[philo->id].mutex);
	pthread_mutex_lock(&philo->sim->fork[philo->sim->nb_philo - philo->id].mutex);
	dead = print_p("is eating", philo);
	pthread_mutex_lock(&philo->sim->eat);
	philo->death_time = get_time() + philo->sim->t_die;
	eating = get_time() + philo->sim->t_eat;
	pthread_mutex_unlock(&philo->sim->eat);
	while (get_time() < eating)
		;
	pthread_mutex_unlock(&philo->sim->fork[philo->sim->nb_philo - philo->id].mutex);
	pthread_mutex_unlock(&philo->sim->fork[philo->id].mutex);
	return (dead);
}
