/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:06:27 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/02/28 19:30:20 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
int	on_destroy(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free_data(data);
	exit(1);
	return (0);
}

// void	location_check(t_data *data, size_t *row, size_t *column)
// {
// 	if (data->map[*row][*column] == COIN)
// 	{
// 		data->map[*row][*column] = EMPTY;
// 		data->coins--;
// 		draw_gamer(data);
// 	}
// 	if (data->map[*row][*column] == EXIT)
// 	{
// 		if (data->coins == 0)
// 			end_game(data);
// 	}
// }


int	on_keypress(int keysim, t_data *data)
{
	if (keysim == ESC)
		return (on_destroy(data), 0);
	// if (keysim == UP && can_move(data, UP) == 1)
	// 	gamer_moves(data, UP);
	// if (keysim == DOWN && can_move(data, DOWN) == 1)
	// 	gamer_moves(data, DOWN);
	// if (keysim == RIGHT && can_move(data, RIGHT) == 1)
	// 	gamer_moves(data, RIGHT);
	// if (keysim == LEFT && can_move(data, LEFT) == 1)
	// 	gamer_moves(data, LEFT);
	// data->move_count++;
	// location_check(data, &data->gamer_pos->row, &data->gamer_pos->column);
	return (0);
}
