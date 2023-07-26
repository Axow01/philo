/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarcott <mmarcott@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:34:46 by mmarcott          #+#    #+#             */
/*   Updated: 2023/07/26 14:13:52 by mmarcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		total;

	i = -1;
	total = 0;
	while (nptr[++i])
		total = (total * 10) + (int)nptr[i] - '0';
	printf("%d\n", total);
	return (total);
}
