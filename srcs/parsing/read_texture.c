/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:39:44 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/25 18:07:56 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_error	path_error(char *line, t_error error)
{
	ft_printf("Error\n");
	if (error == PATH_ERR)
	{
		perror("When trying to open path");
		ft_printf("Invalid path: %s\n", line);
	}
	if (error == PATH_MULTIPLE_ERR)
	{
		ft_printf("Multiple strings when expected one path:\n");
		ft_printf("%s\n", line);
	}
	if (error == PATH_XPM_ERR)
	{
		ft_printf("Invalid path: %s\n", line);
		ft_printf("Path should end with .xpm\n");
	}
	return (error);
}

t_error	check_path(char *line)
{
	int	fd;
	int	i;

	i = 0;
	remove_new_line(line);
	if (ft_count_words(line) != 1)
		return (PATH_MULTIPLE_ERR);
	while (!ft_is_space(line[i]) && line[i] != '\n' && line[i] != '\0')
		i++;
	if (!(line[i - 4] == '.' && line[i - 3] == 'x'
			&& line[i - 2] == 'p' && line[i - 1] == 'm'))
		return (PATH_XPM_ERR);
	line[i] = '\0';
		//remove_new_line(line);
	fd = open(line, O_RDONLY);
	if (fd == -1)
		return (PATH_ERR);
	close(fd);
	return (SUCCESS);
}

/*
	In this function we want to safe the texture path 
	given in the scenefile to our data struct.
	- First we have to skip the beginning of the line as there 
	is the identifier (NO , SO ..) and a space
	- than we have to check if there is a valid path
		- there should be word only
		- the path should end with .xpm !!!!! 
		-
*/

t_error	read_texture(char *line, t_identifier identifier, t_data *data)
{
	char	*pointer;
	t_error	status;

	while (ft_is_space(line[0]))
		line++;
	status = check_path(line);
	if (status != SUCCESS)
		return (path_error(line, status));
	pointer = set_image_pointer(data, identifier, line);
	if (!pointer)
		return (FATAL_MALOC_ERR);
	return (SUCCESS);
}
