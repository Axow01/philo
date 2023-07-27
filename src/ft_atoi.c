/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:34:46 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/27 12:34:05 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

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
