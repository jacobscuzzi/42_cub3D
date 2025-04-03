/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:46:37 by varodrig          #+#    #+#             */
/*   Updated: 2025/04/03 15:47:26 by varodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;
	int	xo;
	int	yo;

	xo = x * MINI_SQUARE_SIZE;
	yo = y * MINI_SQUARE_SIZE;
	i = xo;
	while (i < xo + MINI_SQUARE_SIZE)
	{
		j = yo;
		while (j < yo + MINI_SQUARE_SIZE)
		{
			my_pixel_put(i, j, &data->img, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < data->map_size.row)
	{
		x = 0;
		while (x < data->map_size.column)
		{
			if (data->map[y][x] == '1')
				color = 0xFFFFFF;
			else
				color = 0x000000;
			draw_square(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_player(t_data *data, int size)
{
	int	center_x;
	int	center_y;
	int	scaled_size;
	int	x;
	int	y;

	center_x = (data->px / PX_SIZE) * MINI_SQUARE_SIZE;
	center_y = (data->py / PX_SIZE) * MINI_SQUARE_SIZE;
	scaled_size = (size * MINI_SQUARE_SIZE) / 2;
	x = -scaled_size / 2;
	while (x <= scaled_size / 2)
	{
		y = -scaled_size / 2;
		while (y <= scaled_size / 2)
		{
			my_pixel_put(center_x + x, center_y + y, &data->img, 0xFF0000);
			y++;
		}
		x++;
	}
}

void	draw_ceiling_and_floor(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				my_pixel_put(x, y, &data->img, data->graphics.ceiling.hex);
			else
				my_pixel_put(x, y, &data->img, data->graphics.floor.hex);
			y++;
		}
		x++;
	}
}

void	cub3d_draw(t_data *data)
{
	raycasting(data);
	draw_minimap(data);
	draw_player(data, 2);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img_ptr, 0,
		0);
}
