/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:51:38 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/25 17:06:26 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_tab_to_map(char *row, int j)
{
	row[j] = ' ';
	row[j + 1] = ' ';
	row[j + 2] = ' ';
	row[j + 3] = ' ';
	return (j + 3);
}

char	*fill_map_line(char *line, t_data *data)
{
	int		i;
	int		j;
	char	*row;

	row = (char *)malloc(sizeof(char) * data->map_size.column + 1);
	if (!row)
		return (NULL);
	i = 0;
	j = 0;
	while (j < data->map_size.column)
	{
		if (j < ft_strlen_tab(line))
		{
			if (line[i] == '\t' || line[i] == '\v')
				j = add_tab_to_map(row, j);
			else
				row[j] = line[i];
		}
		else
			row[j] = ' ';
		j++;
		i++;
	}
	row[j] = '\0';
	return (row);
}

t_error	read_map(char *line, t_data *data, int fd)
{
	int	i;

	data->map = (char **)malloc(sizeof(char *) * data->map_size.row);
	if (!data->map)
		return (free_gnl(fd), FATAL_MALOC_ERR);
	data->map[0] = fill_map_line(line, data);
	free(line);
	line = NULL;
	if (!data->map[0])
		return (free_gnl(fd), FATAL_MALOC_ERR);
	i = 1;
	while (i < data->map_size.row)
	{
		line = get_next_line(fd);
		if (!line)
			return (free_gnl(fd), FATAL_MALOC_ERR);
		data->map[i] = fill_map_line(line, data);
		free(line);
		if (!data->map[i])
			return (free_gnl(fd), FATAL_MALOC_ERR);
		i++;
	}
	free_gnl(fd);
	return (SUCCESS);
}
