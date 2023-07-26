/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:22:58 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/26 17:23:30 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->eat);
	printf("%lld %d IS EATING\n", get_time(), philo->id);
	usleep(philo->sim->t_eat * 1000);
	pthread_mutex_unlock(&philo->sim->eat);
}

void	philo_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->think);
	printf("%lld %d IS THINKING\n", get_time(), philo->id);
	pthread_mutex_unlock(&philo->sim->think);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->think);
	printf("%lld %d IS SLEEPING\n", get_time(), philo->id);
	usleep(philo->sim->t_sleep * 1000);
	pthread_mutex_unlock(&philo->sim->think);
}
