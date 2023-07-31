/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 17:22:58 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/31 16:55:30 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	prepare_philo(t_simulation *sim)
{
	int	i;

	sim->fork = malloc(sim->nb_philo * sizeof(t_fork));
	sim->philos = malloc(sim->nb_philo * sizeof(t_philo));
	if (!sim->fork || !sim->philos)
		return (false);
	pthread_mutex_init(&sim->eat, NULL);
	pthread_mutex_init(&sim->death, NULL);
	i = -1;
	while (++i < sim->nb_philo)
	{
		sim->philos[i].id = i;
		sim->philos[i].time_eaten = 0;
		sim->philos[i].sim = sim;
		pthread_mutex_init(&sim->fork[i], NULL);
	}
	return (true);
}

bool	is_death(t_philo *philo)
{
	if (get_time() >= philo->death_time)
	{
		philo->death_time = -1;
		pthread_mutex_lock(&philo->sim->death);
		if (philo->sim->death_philo == 0)
			printf("%lld %d died\n", get_time(), philo->id + 1);
		philo->sim->death_philo += 1;
		pthread_mutex_unlock(&philo->sim->death);
		return (true);
	}
	return (false);
}

bool	sim_death(t_simulation *sim)
{
	pthread_mutex_lock(&sim->death);
	if (sim->death_philo > 0)
	{
		pthread_mutex_unlock(&sim->death);
		return (true);
	}
	pthread_mutex_unlock(&sim->death);
	return (false);
}

bool	philo_sleep(t_philo *philo)
{
	t_time	sleep;

	if (is_death(philo) || get_time() + philo->sim->t_sleep >= philo->death_time)
		return (false);
	sleep = get_time() + philo->sim->t_sleep;
	if (print_p("is sleeping", philo))
		return (false);
	ft_wait(philo->sim->t_sleep);
	return (true);
}

bool	philo_eat(t_philo *philo)
{
	int		id;

	if (is_death(philo) || get_time() + philo->sim->t_eat >= get_time() + philo->sim->t_die)
		return (false);
	id = philo->id - 1;
	if (philo->id == 0)
		id = philo->sim->nb_philo - 1;
	pthread_mutex_lock(&philo->sim->fork[philo->id]);
	print_p("has taken a fork", philo);
	pthread_mutex_lock(&philo->sim->fork[id]);
	print_p("has taken a fork", philo);
	philo->death_time = get_time() + philo->sim->t_die;
	print_p("is eating", philo);
	ft_wait(philo->sim->t_eat);
	pthread_mutex_unlock(&philo->sim->fork[philo->id]);
	pthread_mutex_unlock(&philo->sim->fork[id]);
	if (philo->sim->nb_each_eat)
	{
		philo->time_eaten += 1;
		if (philo->sim->nb_each_eat == philo->time_eaten)
			return (false);
	}
	if (is_death(philo) || sim_death(philo->sim))
		return (false);
	return (true);
}
