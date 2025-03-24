/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:40:38 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/24 17:43:05 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_error	check_elements(t_data *data)
{
	t_scene_check check;

	check = data->scene_check;
	if (check.map == false)
		return (MISS_MAP_ERR);
	if (check.north == 0 || check.south == 0 || check.west == 0 || check.east == 0)	
		return (ft_putstr_fd("Error\nMissing texture in scene file\n", 2), MISS_TEXTURE_ERR);
	if (check.floor == false || check.ceiling == false)
	{
		ft_putstr_fd("Error\nMissing color in scene file\n", 2);
		return (MISS_COLOR_ERR);
	}
	if (check.north > 1 || check.south > 1 || check.west > 1 || check.east > 1)
	{
		ft_putstr_fd("Error\nMultiple textures of the same type in scene file\n", 2);
		return (PATH_MULTIPLE_ERR);
	}
	if (check.floor > 1 || check.ceiling > 1)
	{
		ft_putstr_fd("Error\nMultiple colors of the same type in scene file\n", 2);
		return (MULTIPLE_COLOR_ERR);
	}
	return (SUCCESS);
}


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

void	update_scene_check(t_data *data, char *line, t_line line_type)
{
	t_scene_check	*check;
	t_identifier	identifier;

	check = &data->scene_check;
	if (line_type == L_MAP)
		check->map = true;
	if (line_type == L_IDENTIFIER)
	{
		identifier = is_identifier(line);
		if (identifier == NORTH)
			check->north++;
		else if (identifier == SOUTH)
			check->south++;
		else if (identifier == WEST)
			check->west++;
		else if (identifier == EAST)
			check->east++;
		else if (identifier == FLOOR)
			check->floor = true;
		else if (identifier == CEILING)
			check->ceiling = true;
	}
}

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
		if (data->map_size.column < (int)ft_strlen(line))
			data->map_size.column = (int)ft_strlen(line);
		*map_started = true;
		data->scene_check.map = true;
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
		update_scene_check(data, line, line_type);
		status = check_line_type_status(data, line_type, &map_started, line);
		free(line);
		if (status != SUCCESS)
			return (status);
		line = get_next_line(fd);
	}
	close(fd);
	return (check_elements(data));
}

