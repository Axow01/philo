/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:10:13 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/27 18:43:36 by mmarcott         ###   ########.fr       */
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
	return ((now.tv_sec * 1000 - start.tv_sec * 1000)
		+ (now.tv_usec / 1000 - start.tv_usec / 1000));
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

bool	print_p(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->death);
	if (philo->sim->death_philo == 0 || (philo->death_time == -1
			&& philo->sim->death_philo))
	{
		printf("%lld %d %s\n", get_time(), philo->id + 1, str);
		pthread_mutex_unlock(&philo->sim->death);
		return (true);
	}
	pthread_mutex_unlock(&philo->sim->death);
	return (false);
}

void	*init_philo(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = ptr;
	philo->time_eaten = 0;
	philo->death_time = get_time() + philo->sim->t_die;
	while (philo->death_time >= get_time())
	{
		if (!philo_eat(philo))
			return (NULL);
		if (!print_p("is sleeping", philo))
			return (NULL);
		i = get_time();
		while (get_time() - i < philo->sim->t_sleep)
			;
		if (!print_p("is thinking", philo))
			return (NULL);
	}
	philo->death_time = -1;
	pthread_mutex_lock(&philo->sim->death);
	philo->sim->death_philo += 1;
	pthread_mutex_unlock(&philo->sim->death);
	if (philo->death_time == -1)
		if (print_p("died", philo))
			return (NULL);
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
	sim.fork = malloc(sim.nb_philo * sizeof(pthread_mutex_t));
	sim.death_philo = 0;
	pthread_mutex_init(&sim.eat, NULL);
	pthread_mutex_init(&sim.death, NULL);
	while (++i < sim.nb_philo)
	{
		sim.philos[i].id = i;
		sim.philos[i].sim = &sim;
		pthread_mutex_init(&sim.fork[i], NULL);
		pthread_create(&sim.philos[i].philo, NULL, &init_philo,
			&sim.philos[i]);
	}
	i = -1;
	while (++i < sim.nb_philo)
		if (pthread_join(sim.philos[i].philo, NULL) != 0)
			break ;
	free(sim.philos);
	free(sim.fork);
	return (0);
}
