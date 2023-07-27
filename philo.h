/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 18:16:21 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/26 20:36:46 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>

# define WHITE_SPACE " \t\n\r\v\f"

typedef long long	t_time;

typedef struct s_fork
{
	int				used;
	pthread_mutex_t	mutext;
}		t_fork;

typedef struct s_philo
{
	pthread_t			philo;
	int8_t				id;
	t_fork				fork;
	struct s_simulation	*sim;
}		t_philo;

typedef struct s_simulation
{
	t_philo			*philos;
	pthread_mutex_t	eat;
	pthread_mutex_t	sleep;
	pthread_mutex_t	think;
	int				nb_philo;
	int				nb_each_eat;
	t_time			t_die;
	t_time			t_eat;
	t_time			t_sleep;
}		t_simulation;

/// @brief Calculate the time of the program.
/// @return Return the timestamp of the program (miliseconds).
t_time	get_time(void);

/// @brief This function verifies the args of the main.
/// @param sim The simulation struct.
/// @param args The args of the main.
/// @param argc The nb of args in args.
/// @return True if the parsing is good or false if it's bad.
bool	ft_parsing(t_simulation *sim, const char **args, int8_t argc);

/// @brief Print the error code.
/// @param code the code from 0 to 255.
/// @return The code given.
int8_t	ft_error(int8_t code);

/// @brief Convert a string to a integer.
/// @param nptr The string to convert.
/// @return The converted int.
int		ft_atoi(const char *nptr);

/// @brief The philosopher is eating for the ms specified.
/// @param philo The philosoper's structure.
void	philo_eat(t_philo *philo);

/// @brief The philosoper is thinking.
/// @param philo The philosopher's structure.
void	philo_think(t_philo *philo);

/// @brief The philosoper is sleeping for the ms specified.
/// @param philo The philosopher's structure.
void	philo_sleep(t_philo *philo);

#endif
