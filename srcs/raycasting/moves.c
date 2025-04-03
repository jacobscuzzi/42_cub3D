/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 20:07:16 by varodrig          #+#    #+#             */
/*   Updated: 2025/04/03 15:48:45 by varodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	w_move(t_data *data)
{
	double	new_px;
	double	new_py;
	int		map_x;
	int		map_y;

	new_px = data->px + data->pdx;
	new_py = data->py + data->pdy;
	map_x = (int)(new_px / PX_SIZE);
	map_y = (int)(new_py / PX_SIZE);
	if (data->map[map_y][map_x] == '0' || data->map[map_y][map_x] == 'N')
	{
		data->px += data->pdx;
		data->py += data->pdy;
	}
}

void	s_move(t_data *data)
{
	double	new_px;
	double	new_py;
	int		map_x;
	int		map_y;

	new_px = data->px - data->pdx;
	new_py = data->py - data->pdy;
	map_x = (int)(new_px / PX_SIZE);
	map_y = (int)(new_py / PX_SIZE);
	if (data->map[map_y][map_x] == '0' || data->map[map_y][map_x] == 'N')
	{
		data->px -= data->pdx;
		data->py -= data->pdy;
	}
}

void	a_move(t_data *data)
{
	double	new_px;
	double	new_py;
	int		map_x;
	int		map_y;

	new_px = data->px + cos(data->gamer_dir - PI / 2) * 5;
	new_py = data->py + sin(data->gamer_dir - PI / 2) * 5;
	map_x = (int)(new_px / PX_SIZE);
	map_y = (int)(new_py / PX_SIZE);
	if (data->map[map_y][map_x] == '0' || data->map[map_y][map_x] == 'N')
	{
		data->px = new_px;
		data->py = new_py;
	}
}

void	d_move(t_data *data)
{
	double	new_px;
	double	new_py;
	int		map_x;
	int		map_y;

	new_px = data->px + cos(data->gamer_dir + PI / 2) * 5;
	new_py = data->py + sin(data->gamer_dir + PI / 2) * 5;
	map_x = (int)(new_px / PX_SIZE);
	map_y = (int)(new_py / PX_SIZE);
	if (data->map[map_y][map_x] == '0' || data->map[map_y][map_x] == 'N')
	{
		data->px = new_px;
		data->py = new_py;
	}
}
