/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:56:17 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/08/13 18:17:44 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// int	ft_isblank(const char c)
// {
// 	if (c == 32)
// 		return (1);
// 	if (c >= 7 && c <= 13)
// 		return (1);

// 	return (0);
// }

int	ft_atoi(const char *str)
{
	int	i;
	int	counter;
	int	negator;

	negator = 1;
	i = 0;
	counter = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			negator *= -1;
		i++;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		counter = counter * 10 + str[i] - 48;
		i++;
	}
	return (counter * negator);
}
