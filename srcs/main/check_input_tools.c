/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:51:00 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/03 15:07:32 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_map_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

bool	check_if_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (true);
	return (false);
}