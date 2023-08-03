/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:34:46 by mmarcott          #+#    #+#             */
/*   Updated: 2023/08/03 14:56:32 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	change_status_fork(t_philo *philo, int8_t status)
{
	int	id;

	id = philo->id - 1;
	if (philo->id == 0)
		id = philo->sim->nb_philo - 1;
	pthread_mutex_lock(&philo->sim->eat);
	philo->sim->fork_status[philo->id] = status;
	philo->sim->fork_status[id] = status;
	pthread_mutex_unlock(&philo->sim->eat);
}

bool	ft_check_forks(t_philo *philo, int8_t *forks)
{
	int	id;

	id = philo->id - 1;
	if (philo->id == 0)
		id = philo->sim->nb_philo - 1;
	pthread_mutex_lock(&philo->sim->eat);
	if (forks[id] == 0 && forks[philo->id] == 0)
	{
		pthread_mutex_unlock(&philo->sim->eat);
		return (true);
	}
	pthread_mutex_unlock(&philo->sim->eat);
	return (false);
}

void	ft_destroy_all_mutex(t_simulation *sim)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(&sim->eat);
	pthread_mutex_destroy(&sim->death);
	while (++i < sim->nb_philo)
		pthread_mutex_destroy(&sim->fork[i]);
}

void	ft_wait(t_time duration)
{
	t_time	new;

	new = get_time() + duration;
	while (new > get_time())
		usleep(200);
}

int	ft_atoi(const char *nptr)
{
	size_t			i;
	long int		total;

	i = -1;
	total = 0;
	if (ft_strlen((char *)nptr) > 11)
		return (-1);
	while (nptr[++i])
		total = (total * 10) + (int)nptr[i] - '0';
	if (total < 0 || total > INT32_MAX)
		total = -1;
	return (total);
}
