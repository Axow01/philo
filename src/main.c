/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:10:13 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/31 14:15:51 by mmarcott         ###   ########.fr       */
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
	philo_death(philo);
	pthread_mutex_lock(&philo->sim->death);
	if (philo->sim->death_philo == 0)
	{
		printf("%lld %d %s\n", get_time(), philo->id + 1, str);
		pthread_mutex_unlock(&philo->sim->death);
		return (false);
	}
	pthread_mutex_unlock(&philo->sim->death);
	return (philo_death(philo));
}

void	*init_philo(void *ptr)
{
	t_philo	*philo;
	int		i;

	philo = ptr;
	if (philo->id % 2 == 0)
		usleep((philo->sim->t_eat * 1000) / 2);
	philo->time_eaten = 0;
	philo->death_time = get_time() + philo->sim->t_die;
	while (philo->death_time >= get_time())
	{
		if (philo->sim->nb_philo == 1 || (philo->sim->t_die <= philo->sim->t_eat || philo->sim->t_die <= philo->sim->t_sleep))
			break ;
		if (philo_eat(philo))
			return (NULL);
		if (print_p("is sleeping", philo))
			return (NULL);
		i = get_time();
		while (get_time() - i < philo->sim->t_sleep)
			usleep(1000);
		if (print_p("is thinking", philo))
			return (NULL);
	}
	while (!philo_death(philo))
		usleep(500);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_simulation	sim;
	int				i;

	if (argc != 5 && argc != 6)
		return (ft_error(10));
	i = -1;
	if (!ft_parsing(&sim, (const char **)argv, argc))
		return (ft_error(11));
	while (++i < sim.nb_philo)
		if (pthread_join(sim.philos[i].philo, NULL) != 0)
			break ;
	free(sim.philos);
	free(sim.fork);
	return (0);
}
