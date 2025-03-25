/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:47:44 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/24 19:28:39 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"


void	clean_up(t_data *data)
{
	int	i;

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