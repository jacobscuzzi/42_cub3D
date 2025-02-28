/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:51:51 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/02/28 18:04:02 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
int	fill_map(t_data *data, int fd)
{
	char		*cache;
	size_t		column;
	size_t		row;

	column = 0;
	row = 0;
	while (row < data->dim->row)
	{
		cache = get_next_line(fd);
		if (!cache)
			return (1);
		while (column < data->dim->column)
		{
			data->map[row][column] = cache[column];
			column++;
		}
		column = 0;
		row++;
		free(cache);
	}
	(void)get_next_line(fd);
	*data->gamer_pos = find_element(data, GAMER);
	return (0);
}

void	clone_map(char **map_clone, t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < data->dim->row)
	{
		j = 0;
		while (j < data->dim->column)
		{
			map_clone[i][j] = data->map[i][j];
			j++;
		}
		i++;
	}
}
