/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:10:13 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/26 14:56:47 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

t_time	get_time(void)
{
	static struct timeval	start = {-1, -1};
	struct timeval			now;

	if (start.tv_sec == -1 && start.tv_usec == -1)
		gettimeofday(&start, NULL);
	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000 - start.tv_sec * 1000) + 
		(now.tv_usec / 1000 - start.tv_usec / 1000));
}

int8_t	ft_error(int8_t code)
{
	char	c;
	int		b;

	write(2, "Error\nCode: ", 13);
	b = code;
	while (b > 0)
	{
		c = (b / 10) + '0';
		write(2, &c, 1);
		b /= 10;
	}
	write(2, "\n", 1);
	return (code);
}

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

void	*init_philo(void *ptr)
{
	t_philo	*philo;

	philo = ptr;
	philo->fork.used = 0;
	philo_think(philo);
	philo_eat(philo);
	philo_sleep(philo);
	return (NULL);
}


int	main(int argc, char **argv)
{
	t_simulation	sim;
	int8_t			i;

	if (argc != 5 && argc != 6)
		return (ft_error(10));
	i = -1;
	get_time();
	if (!ft_parsing(&sim, (const char **)argv, argc))
		return (ft_error(11));
	sim.philos = malloc(sim.nb_philo * sizeof(t_philo));
	pthread_mutex_init(&sim.think, NULL);
	pthread_mutex_init(&sim.eat, NULL);
	pthread_mutex_init(&sim.sleep, NULL);
	while (++i < sim.nb_philo)
	{
		sim.philos[i].id = i;
		sim.philos[i].sim = &sim;
		pthread_create(&sim.philos[i].philo, NULL, init_philo, &sim.philos[i].philo);
	}
	while (1)
		;
	return (0);
}
