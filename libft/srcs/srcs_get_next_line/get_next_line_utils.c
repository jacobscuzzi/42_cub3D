/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 17:36:39 by jbaumfal          #+#    #+#             */
/*   Updated: 2024/08/13 19:17:17 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strchr_pos(const char *s, int c)
{
	int		i;
	char	a;

	a = (char)c;
	i = 0;
	while (s[i])
	{
		if (s[i] == a)
			return (i + 1);
		i++;
	}
	return (-1);
}
