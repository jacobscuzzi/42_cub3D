/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:46:11 by varodrig          #+#    #+#             */
/*   Updated: 2025/04/03 14:55:29 by varodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

float	init_horizontal_ray(t_data *data, t_ray_params *ray_params)
{
	float	invtan;

	invtan = -1 / tan(ray_params->first_ray);
	if (ray_params->first_ray == 0 || ray_params->first_ray == PI)
		return (8);
	if (ray_params->first_ray > PI)
	{
		ray_params->ry = (floor(data->py / PX_SIZE) * PX_SIZE) - 0.0001;
		ray_params->rx = (data->py - ray_params->ry) * invtan + data->px;
		ray_params->yo = -PX_SIZE;
		ray_params->xo = -(ray_params->yo) * invtan;
	}
	else
	{
		ray_params->ry = (floor(data->py / PX_SIZE) * PX_SIZE) + PX_SIZE;
		ray_params->rx = (data->py - ray_params->ry) * invtan + data->px;
		ray_params->yo = PX_SIZE;
		ray_params->xo = -(ray_params->yo) * invtan;
	}
	return (0);
}

float	init_vertical_ray(t_data *data, t_ray_params *ray_params)
{
	float	ntan;

	ntan = -tan(ray_params->first_ray);
	if (ray_params->first_ray == PI / 2 || ray_params->first_ray == 3 * PI / 2)
		return (8);
	if (ray_params->first_ray > PI / 2 && ray_params->first_ray < 3 * PI / 2)
	{
		ray_params->rx = (floor(data->px / PX_SIZE) * PX_SIZE) - 0.01;
		ray_params->ry = (data->px - ray_params->rx) * ntan + data->py;
		ray_params->xo = -PX_SIZE;
		ray_params->yo = -(ray_params->xo) * ntan;
	}
	else
	{
		ray_params->rx = (floor(data->px / PX_SIZE) * PX_SIZE) + PX_SIZE;
		ray_params->ry = (data->px - ray_params->rx) * ntan + data->py;
		ray_params->xo = PX_SIZE;
		ray_params->yo = -(ray_params->xo) * ntan;
	}
	return (0);
}

float	check_horizontal_lines(t_data *data, float first_ray, float *hx,
		float *hy)
{
	t_ray_params	ray_params;
	int				dof;
	float			wall_distance_h;

	dof = 0;
	wall_distance_h = 1000000;
	ray_params.first_ray = first_ray;
	dof = init_horizontal_ray(data, &ray_params);
	while (dof < data->map_size.row)
	{
		if (get_map_position(data, ray_params.rx, ray_params.ry))
		{
			wall_distance_h = sqrt((ray_params.rx - data->px) * (ray_params.rx
						- data->px) + (ray_params.ry - data->py)
					* (ray_params.ry - data->py));
			*hx = ray_params.rx;
			*hy = ray_params.ry;
			return (wall_distance_h);
		}
		ray_params.rx += ray_params.xo;
		ray_params.ry += ray_params.yo;
		dof++;
	}
	return (wall_distance_h);
}

float	check_vertical_lines(t_data *data, float first_ray, float *vx,
		float *vy)
{
	t_ray_params	ray_params;
	int				dof;
	float			wall_distance_v;

	dof = 0;
	wall_distance_v = 1000000;
	ray_params.first_ray = first_ray;
	dof = init_vertical_ray(data, &ray_params);
	while (dof < data->map_size.column)
	{
		if (get_map_position(data, ray_params.rx, ray_params.ry))
		{
			wall_distance_v = sqrt((ray_params.rx - data->px) * (ray_params.rx
						- data->px) + (ray_params.ry - data->py)
					* (ray_params.ry - data->py));
			*vx = ray_params.rx;
			*vy = ray_params.ry;
			return (wall_distance_v);
		}
		ray_params.rx += ray_params.xo;
		ray_params.ry += ray_params.yo;
		dof++;
	}
	return (wall_distance_v);
}
