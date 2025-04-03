/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:46:19 by varodrig          #+#    #+#             */
/*   Updated: 2025/04/03 16:23:43 by varodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

void	init_draw_params(t_draw *d, float disT)
{
	d->lineh = (PX_SIZE * HEIGHT) / disT;
	d->lineoffset = (HEIGHT - d->lineh) / 2;
	d->ratio = 64.0 / d->lineh;
	d->tex_pos = 0;
	d->slice_width = WIDTH / NUM_RAYS;
	if (d->lineh > HEIGHT)
	{
		d->tex_pos = (d->lineh - HEIGHT) / 2.0 * d->ratio;
		d->lineh = HEIGHT;
		d->lineoffset = 0;
	}
}

void	draw_texture_line(t_data *data, t_draw *d, int tex_x)
{
	int			color;
	t_texture	*current;

	current = get_wall_texture(data);
	color = *(int *)(current->addr + (d->tex_y * current->line_length + tex_x
				* (current->bits_per_pixel / 8)));
	my_pixel_put(d->rx, d->ry, &data->img, color);
}

void	draw_wall_slice(t_data *data, int r, float disT, int tex_x)
{
	t_draw	d;
	int		i;
	int		j;

	init_draw_params(&d, disT);
	i = -1;
	while (++i < d.slice_width)
	{
		j = -1;
		d.tex_current = d.tex_pos;
		while (++j < d.lineh)
		{
			d.tex_y = (int)d.tex_current % 64;
			d.rx = r * d.slice_width + i;
			d.ry = j + d.lineoffset;
			draw_texture_line(data, &d, tex_x);
			d.tex_current += d.ratio;
		}
	}
}

float	set_wall_direction(t_data *data, float dist_h, float dist_v, t_ray *ray)
{
	if (dist_v < dist_h)
	{
		ray->tex_x = ((int)fabs(ray->vy)) % 64;
		if (ray->angle > PI / 2 && ray->angle < 3 * PI / 2)
			data->direction = D_WEST;
		else
			data->direction = D_EAST;
		return (dist_v);
	}
	ray->tex_x = ((int)fabs(ray->hx)) % 64;
	if (ray->angle > PI)
		data->direction = D_NORTH;
	else
		data->direction = D_SOUTH;
	return (dist_h);
}

void	raycasting(t_data *data)
{
	t_ray	ray;
	int		r;
	float	raysfield;

	r = -1;
	draw_ceiling_and_floor(data);
	init_ray_casting(data, &ray, &raysfield);
	while (++r < NUM_RAYS)
	{
		ray.dist_h = check_horizontal_lines(data, ray.angle, &ray.hx, &ray.hy);
		ray.dist_v = check_vertical_lines(data, ray.angle, &ray.vx, &ray.vy);
		ray.dist = set_wall_direction(data, ray.dist_h, ray.dist_v, &ray);
		ray.dist = fix_fisheye(ray.dist, data->gamer_dir, ray.angle);
		draw_wall_slice(data, r, ray.dist, ray.tex_x);
		ray.angle = normalize_angle(ray.angle + raysfield);
	}
}
