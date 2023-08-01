/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:34:46 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/31 21:36:44 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_wait(t_time duration)
{
	t_time	new;

	new = get_time() + duration;
	while (new > get_time())
		usleep(500);
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
