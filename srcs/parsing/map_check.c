/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:24:39 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/22 15:50:09 by varodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_surrounded(t_data *data, int row, int column)
{
	if (row == 0 || row == data->map_size.row)
		return (false);
	if (column == 0 || column == data->map_size.column)
		return (false);
	if (data->map[row - 1][column] == ' ' || data->map[row + 1][column] == ' ')
		return (false);
	if (data->map[row][column - 1] == ' ' || data->map[row][column + 1] == ' ')
		return (false);
	return (true);
}

bool	is_player(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (true);
	return (false);
}

void	read_player(t_data *data, int row, int column)
{
	data->gamer_pos.row = row;
	data->gamer_pos.column = column;
	if (data->map[row][column] == 'E')
		data->gamer_dir = 0;
	else if (data->map[row][column] == 'N')
		data->gamer_dir = 3 * PI / 2;
	else if (data->map[row][column] == 'W')
		data->gamer_dir = PI;
	else if (data->map[row][column] == 'S')
		data->gamer_dir = PI / 2;
}

t_error player_check(int player_count)
{
	if (player_count == 0)
		return (NO_GAMER_ERR);
	if (player_count > 1)
		return (MULTIPLE_GAMER_ERR);
	return (SUCCESS);
}

t_error map_check(t_data *data)
{
	int	row;
	int	column;
	int		player_count;
	
	player_count = 0;
	row = 0;

	while (row < data->map_size.row)
	{
		column = 0;
		while (column < data->map_size.column)
		{
			if (is_player(data->map[row][column]))
			{
				player_count++;
				read_player(data, row, column);
				data->map[row][column] = '0';
			}
			if (data->map[row][column] == '0' && !is_surrounded(data, row, column))
				return (MAP_ERR);
			column++;
		}
		row++;
	}
	return (player_check(player_count));
}
