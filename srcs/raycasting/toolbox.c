/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolbox.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:37:54 by varodrig          #+#    #+#             */
/*   Updated: 2025/04/03 15:55:00 by varodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (NULL == s || fd < 0)
		return ;
	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_error_ray(void)
{
	ft_putstr_fd("malloc failed\n", STDERR_FILENO);
	exit(1);
}

void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		offset = (y * img->line_len) + (x * (img->bpp / 8));
		*(unsigned int *)(img->pix_ptr + offset) = color;
	}
}

int	get_map_position(t_data *data, float rx, float ry)
{
	int	mx;
	int	my;

	mx = (int)(rx / PX_SIZE);
	my = (int)(ry / PX_SIZE);
	if (mx >= 0 && mx < data->map_size.column && my >= 0
		&& my < data->map_size.row)
	{
		if (data->map[my][mx] == '1')
			return (1);
	}
	return (0);
}

float	normalize_angle(float angle)
{
	while (angle < 0)
		angle += 2 * PI;
	while (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}
