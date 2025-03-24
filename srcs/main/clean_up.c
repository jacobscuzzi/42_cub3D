/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:47:44 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/24 15:47:45 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"


void	end_game(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	exit(1);
}

void	clean_data(t_data *data)
{
	size_t	i;

	i = 0;
	if (data->map)
	{
		while (i < data->map_size.row)
		{
			free(data->map[i]);
			i++;
		}
		free(data->map);
	}
	if (data->graphics.north)
		free(data->graphics.north);
	if (data->graphics.south)
		free(data->graphics.south);
	if (data->graphics.west)
		free(data->graphics.west);
	if (data->graphics.east)
		free(data->graphics.east);
	free(data);
}

void 	clean_up(t_data *data)
{
	//end_game(data);
	clean_data(data);
}