/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 21:47:58 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/02/28 18:04:02 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
int	wall_check(t_data *data)
{
	size_t	column;
	size_t	row;

	column = 0;
	row = 0;
	while (column < data->dim->column)
	{
		if (data->map[0][column] != '1')
			return (0);
		if (data->map[data->dim->row - 1][column] != '1')
			return (0);
		column++;
	}
	while (row < data->dim->row)
	{
		if (data->map[row][0] != '1')
			return (0);
		if (data->map[row][data->dim->column - 1] != '1')
			return (0);
		row++;
	}
	return (1);
}

int	char_check(t_data *data)
{
	size_t	row;
	size_t	column;

	row = 0;
	column = 0;
	while (row < data->dim->row)
	{
		while (column < data->dim->column)
		{
			if (ft_strchr("01EPC", data->map[row][column]) == NULL)
				return (0);
			column++;
		}
		column = 0;
		row++;
	}
	return (1);
}

void	map_flood(char **map_clone, t_coord *dim, size_t row, size_t column)
{
	if (!(ft_strchr("0PCE", map_clone[row][column])))
		return ;
	if (row >= dim->row)
		return ;
	if (row < 0)
		return ;
	if (column >= dim->column)
		return ;
	if (column < 0)
		return ;
	map_clone[row][column] = 'F';
	map_flood(map_clone, dim, row + 1, column);
	map_flood(map_clone, dim, row - 1, column);
	map_flood(map_clone, dim, row, column + 1);
	map_flood(map_clone, dim, row, column - 1);
	return ;
}

int	map_solve(t_data *data, char **map_clone)
{
	map_flood(map_clone, data->dim,
		data->gamer_pos->row, data->gamer_pos->column);
	ft_printf("Flooded data:\n");
	if (count_element(data, EXIT, map_clone) > 0
		|| count_element(data, 'C', map_clone) > 0)
		return (0);
	return (1);
}

int	map_check(t_data *data)
{
	int		exit;
	int		gamer_pos;
	char	**map_clone;

	exit = count_element(data, EXIT, data->map);
	gamer_pos = count_element(data, GAMER, data->map);
	data->coins = count_element(data, COIN, data->map);
	if (char_check(data) == 0)
		return (0);
	if (exit != 1 || gamer_pos != 1 || data->coins == 0)
		return (0);
	map_clone = init_map(data->dim);
	if (!map_clone)
		return (0);
	clone_map(map_clone, data);
	if (map_solve(data, map_clone) == 0)
		return (free_all(map_clone, *data->dim), -1);
	free_all(map_clone, *data->dim);
	return (1);
}
