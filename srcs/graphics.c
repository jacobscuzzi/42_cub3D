/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 23:18:08 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/02/28 19:26:36 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
void	draw_floor(t_data *data)
{
	data->img = mlx_xpm_file_to_image(data->mlx,
			"./img/floor.xpm", &data->pxl, &data->pxl);
	mlx_put_image_to_window (data->mlx, data->mlx_win,
		data->img, data->pxl * data->pos.column,
		data->pxl * data->pos.row);
	mlx_destroy_image(data->mlx, data->img);
}