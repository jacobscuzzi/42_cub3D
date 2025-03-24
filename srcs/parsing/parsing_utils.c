/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:06:35 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/24 18:27:16 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_count_words(char *line)
{
	int i;
	int words;

	i = 0;
	words = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			words++;
			while (line[i] && line[i] != ' ')
				i++;
		}
		else
			i++;
	}
	return (words);
}

char *set_image_pointer(t_data *data, t_identifier type, char *line)
{
	char *pointer;

	pointer = NULL;
	ft_printf("set image pointer with line: %s\n", line);
	if (type == NORTH)
	{
		data->graphics.north = ft_strdup(line);
		pointer = data->graphics.north;
	}
	else if (type == SOUTH)
	{
		data->graphics.south = ft_strdup(line);
		pointer = data->graphics.south;
	}
	else if (type == WEST)
	{
		data->graphics.west = ft_strdup(line);
		pointer = data->graphics.west;
	}
	else if (type == EAST)
	{
		data->graphics.east = ft_strdup(line);
		pointer = data->graphics.east;
	}
	return (pointer);
}

void	free_gnl(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
}

void remove_new_line(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != '\n' && line[i] != '\0')
		i++;
	line[i] = '\0';
}