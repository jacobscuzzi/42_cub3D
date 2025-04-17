/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:42:57 by varodrig          #+#    #+#             */
/*   Updated: 2025/04/17 15:02:17 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycasting.h"

// beceause FPV = PI/3 so 0<cos(a)<1
float	fix_fisheye(float distance, float gamer_dir, float ray_angle)
{
	float	ca;

	ca = normalize_angle(gamer_dir - ray_angle);
	return (distance * cos(ca));
}

void	init_ray_casting(t_data *data, t_ray *ray, float *raysfield)
{
	float	fov;

	fov = PI / 3;
	*raysfield = fov / NUM_RAYS;
	ray->angle = normalize_angle(data->gamer_dir - fov / 2);
}

t_texture	*get_wall_texture(t_data *data)
{
	if (data->direction == D_NORTH)
		return (&data->north_texture);
	if (data->direction == D_SOUTH)
		return (&data->south_texture);
	if (data->direction == D_WEST)
		return (&data->west_texture);
	return (&data->east_texture);
}
