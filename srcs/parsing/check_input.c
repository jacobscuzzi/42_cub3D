/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:40:38 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/25 17:06:08 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_error	check_elements(t_data *data)
{
	t_scene_check	check;

	check = data->scene_check;
	if (check.map == false)
		return (MISS_MAP_ERR);
	if (check.north == 0 || check.south == 0
		|| check.west == 0 || check.east == 0)
		return (ft_putstr_fd("Error\nMissing texture\n", 2), MISS_TEXTURE_ERR);
	if (check.floor == false || check.ceiling == false)
	{
		ft_putstr_fd("Error\nMissing color in scene file\n", 2);
		return (MISS_COLOR_ERR);
	}
	if (check.north > 1 || check.south > 1 || check.west > 1 || check.east > 1)
	{
		ft_putstr_fd("Error\nThe same texture indormation is given twice\n", 2);
		return (PATH_MULTIPLE_ERR);
	}
	if (check.floor > 1 || check.ceiling > 1)
	{
		ft_putstr_fd("Error\nThe same colour indormation is given twice\n", 2);
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
	if (argv[1][i - 4] == '/' || ft_strlen(argv[1]) < 5)
		return (INPUT_ERR);
	return (SUCCESS);
}

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
			check->floor++;
		else if (identifier == CEILING)
			check->ceiling++;
	}
}

t_error	check_line_type_status(t_data *data, t_line line_type, char *line)
{
	if (line_type == L_EMPTY)
	{
		if (data->scene_check.map == true)
			data->scene_check.map_ended = true;
		return (SUCCESS);
	}
	if (line_type == L_IDENTIFIER)
	{
		if (data->scene_check.map == true)
			return (MAP_LINE_ERR);
		return (SUCCESS);
	}
	if (line_type == L_MAP)
	{
		if (data->scene_check.map_ended == true)
			return (MAP_EMPTY_LINE_ERR);
		data->map_size.row++;
		if (data->map_size.column < ft_strlen_tab(line))
			data->map_size.column = ft_strlen_tab(line);
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
	t_line			line_type;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (OPEN_ERR);
	line = NULL;
	line = get_next_line(fd);
	if (!line)
		return (close(fd), FATAL_MALOC_ERR);
	while (line)
	{
		line_type = check_scenefile_line(line);
		update_scene_check(data, line, line_type);
		status = check_line_type_status(data, line_type, line);
		free(line);
		if (status != SUCCESS)
			return (free_gnl(fd), close(fd), status);
		line = get_next_line(fd);
	}
	free_gnl(fd);
	close(fd);
	return (check_elements(data));
}
