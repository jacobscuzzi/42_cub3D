/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:46:33 by varodrig          #+#    #+#             */
/*   Updated: 2025/04/03 16:17:59 by varodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		ft_error_ray();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "data");
	if (!data->win_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		ft_error_ray();
	}
	data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	if (!data->img.img_ptr)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		ft_error_ray();
	}
	data->img.pix_ptr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	init_parameters(data);
}

int	end_data_error(t_data *data)
{
	if (data->north_texture.img)
		mlx_destroy_image(data->mlx_ptr, data->north_texture.img);
	if (data->south_texture.img)
		mlx_destroy_image(data->mlx_ptr, data->south_texture.img);
	if (data->east_texture.img)
		mlx_destroy_image(data->mlx_ptr, data->east_texture.img);
	if (data->west_texture.img)
		mlx_destroy_image(data->mlx_ptr, data->west_texture.img);
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	clean_up(data);
    ft_putstr_fd("Error\nFailed to load texture\n", STDERR_FILENO);
	exit(1);
}

int	end_data(t_data *data)
{
	if (data->north_texture.img)
		mlx_destroy_image(data->mlx_ptr, data->north_texture.img);
	if (data->south_texture.img)
		mlx_destroy_image(data->mlx_ptr, data->south_texture.img);
	if (data->east_texture.img)
		mlx_destroy_image(data->mlx_ptr, data->east_texture.img);
	if (data->west_texture.img)
		mlx_destroy_image(data->mlx_ptr, data->west_texture.img);
	if (data->img.img_ptr)
		mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
	if (data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	clean_up(data);
	exit(0);
}

void	load_texture(t_data *data, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(data->mlx_ptr, path, &texture->width,
			&texture->height);
	if (!texture->img)
        end_data_error(data);
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
}

void	init_parameters(t_data *data)
{
	load_texture(data, &data->north_texture, data->graphics.north);
	load_texture(data, &data->south_texture, data->graphics.south);
	load_texture(data, &data->west_texture, data->graphics.west);
	load_texture(data, &data->east_texture, data->graphics.east);
	data->px = (data->gamer_pos.column) * PX_SIZE + (PX_SIZE / 2);
	data->py = (data->gamer_pos.row) * PX_SIZE + (PX_SIZE / 2);
	data->pdx = cos(data->gamer_dir) * 5;
	data->pdy = sin(data->gamer_dir) * 5;
}
