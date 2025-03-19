/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:26:12 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/19 20:30:48 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_error read_map(char *line, t_data *data, int fd)
{
	size_t	i;

	data->map = (char **)malloc(sizeof(char *) * data->map_size.row);
	data->map[0] = ft_strdup(line);
	free(line);
	line = NULL;
	i = 1;
	while (i < data->map_size.row)
	{
		data->map[i] = get_next_line(fd);
		if (!data->map[i])
			return (FATAL_MALOC_ERR);
		i++;
		free(line);
		line = NULL;
	}
	return (SUCCESS);
}

/*
	In the beginning we skip spaces for the case that there is a space before the identifier.
	Then we check if the identifier is a texture or a color.
	- If it is a texture we call the read_texture function
	- If it is a color we call the read_color function
	- If the identifier is not valid we return an error

*/
t_error read_identifier(char *line, t_data *data)
{
    t_identifier    identifier;
	t_error			status;

	while (line[0] && line[0] == ' ')
		line++;
    identifier = is_identifier(line);
	if (identifier == NORTH || identifier == SOUTH || identifier == WEST || identifier == EAST)
		status = read_texture(line + 3, identifier, data);
	else
		status = read_color(line + 2, identifier, data);
	return (status);
}


t_error read_scenefile(int fd, t_data *data)
{
	t_error		status;
	char		*line;
	t_line line_type;

	line = get_next_line(fd);
	while (line)
	{
		line_type = check_scenefile_line(line);
		if (line_type == L_IDENTIFIER)
			status = read_identifier(line, data);
		else if (line_type == L_EMPTY)
			status = SUCCESS;
		else if (line_type == L_MAP)
			return(read_map(line, data, fd));
		else
			status = SCENE_LINE_ERR;
		if (status != SUCCESS)
			return (free(line), status);
		free(line);
		line = get_next_line(fd);
		ft_printf("line read\n");
	}
	return (status);
}


/*
	Before we start to parse the data we check the validity of the input.

	- In a first step we check if the general format of the input is correct (1 argument, argument is a .cub file)
	- In a second step we check if the file can be opened and if the file is a valid scene file
		- for this we check line for line in the check_scenefile_line function
	- When all of the above was succesful we then open the file again and start to parse the data (read_scenefile) 
*/

t_error parsing(int argc, char **argv, t_data *data)
{
	t_error status;
	int     fd;

	status = check_format(argc, argv);
	if (status != SUCCESS)
		return (status);
	ft_printf("format checked\n");
	status = check_scene_file(data, argv[1]);
	if (status != SUCCESS)
		return (status);
	ft_printf("scene file checked\n");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (OPEN_ERR);
	status = read_scenefile(fd, data);
	close(fd);
	ft_printf("Scenefile read\n");
	if (status != SUCCESS)
		return (status);
	status = map_check(data);
	if (status != SUCCESS)
		ft_printf("Map is invalid\n");
	else
		ft_printf("Map is valid\n");
	return (status);
}
