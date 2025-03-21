/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:40:38 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/20 19:00:23 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_error	check_format(int argc, char **argv)
{
	int	i;

	if (argc != 2)
		return (INPUT_ERR);
	if (argv[1][0] == '\0')
		return (INPUT_ERR);
	i = ft_strlen(argv[1]) - 1;
	if (!(argv[1][i] == 'b' && argv[1]
		[i - 1] == 'u' && argv[1][i - 2] == 'c' && argv[1][i - 3] == '.'))
		return (INPUT_ERR);
	if(argv[1][i - 4] == '/' || ft_strlen(argv[1]) < 5)
		return (INPUT_ERR);
	return (SUCCESS);
}

/*
t_error	check_map(int fd, char *line)
{
	int		i;

	i = 0;
	while (line)
	{
		while (line[i])
		{
			if (line[i] == ' ')
				i++;
			else
			{
				if (is_map_char(line[i]) == false)
					return (MAP_ERROR);
				i++;
			}
		}
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	return (SUCCESS);
}
*/

t_error	check_line_type_status(t_data *data, t_line line_type, bool *map_started, char *line)
{
	if (line_type == L_EMPTY)
		return (SUCCESS);
	if (line_type == L_IDENTIFIER)
	{
		if (*map_started == true)
		{
			ft_putstr_fd("Error\n Map has to be last element in scenefile\n", 2);
			return (SCENE_LINE_ERR);
		}
		return (SUCCESS);
	}
	if (line_type == L_MAP)
	{
		data->map_size.row++;
		if (data->map_size.column < ft_strlen(line))
			data->map_size.column = ft_strlen(line);
		*map_started = true;
		return (SUCCESS);
	}
	if (line_type == L_INVALID)
		return (SCENE_LINE_ERR);
	return (FATAL_MALOC_ERR);
}


t_error	check_scene_file(t_data *data, char *path)
{
	int				fd;
	char			*line;
	t_error			status;
	t_line	line_type;
	bool			map_started;

	map_started = false;
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (OPEN_ERR);
	line = NULL;
	line = get_next_line(fd);
	if (!line)
		return (FATAL_MALOC_ERR);
	while (line)
	{
		line_type = check_scenefile_line(line);
		status = check_line_type_status(data, line_type, &map_started, line);
		free(line);
		if (status != SUCCESS)
			return (status);
		line = get_next_line(fd);
	}
	close(fd);
	return (status);
}
