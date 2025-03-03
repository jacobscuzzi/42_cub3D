/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 18:08:30 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/03 15:27:40 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
int	can_move(t_data *data, int direction)
{
	long	pos_row;
	long	pos_column;

	pos_row = (long)(data->gamer_pos->row);
	pos_column = (long)(data->gamer_pos->column);
	if (direction == UP)
		pos_row --;
	if (direction == DOWN)
		pos_row ++;
	if (direction == RIGHT)
		pos_column ++;
	if (direction == LEFT)
		pos_column --;
	if (pos_row < 0 || pos_column < 0)
		return (0);
	if (data->map[pos_row][pos_column] == WALL)
		return (0);
	return (1);
}
*/