/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:30:39 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/04/03 15:46:56 by varodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	right_move(t_data *data)
{
	data->gamer_dir += 0.05;
	if (data->gamer_dir > 2 * PI)
		data->gamer_dir -= 2 * PI;
	data->pdx = cos(data->gamer_dir) * 5;
	data->pdy = sin(data->gamer_dir) * 5;
}

void	left_move(t_data *data)
{
	data->gamer_dir -= 0.05;
	if (data->gamer_dir < 0)
		data->gamer_dir += 2 * PI;
	data->pdx = cos(data->gamer_dir) * 5;
	data->pdy = sin(data->gamer_dir) * 5;
}

int	moves(int key, t_data *data)
{
	if (key == XK_Escape)
		end_data(data);
	else if (key == XK_Right)
		right_move(data);
	else if (key == XK_Left)
		left_move(data);
	else if (key == XK_w)
		w_move(data);
	else if (key == XK_s)
		s_move(data);
	else if (key == XK_a)
		a_move(data);
	else if (key == XK_d)
		d_move(data);
	cub3d_draw(data);
	return (0);
}

void	init_events(t_data *data)
{
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &moves, data);
	mlx_hook(data->win_ptr, DestroyNotify, 0, end_data, data);
}

int	cub_3d(t_data *data)
{
	init_mlx(data);
	cub3d_draw(data);
	init_events(data);
	mlx_loop(data->mlx_ptr);
	return (SUCCESS);
}
