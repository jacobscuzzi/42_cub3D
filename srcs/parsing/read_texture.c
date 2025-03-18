/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:39:44 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/18 18:20:04 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_error path_error(char *line, t_error error)
{
	ft_printf("Error\n");
	if (error == PATH_ERR)
	{
		perror("Invalid path");
		ft_printf("%s", line);
	}
	if (error == PATH_MULTIPLE_ERR)
	{
		ft_printf("Multiple strings when expected one path:\n");
		ft_printf("%s\n", line);
	}
	return (error);
}

t_error check_path(char *line)
{
	int	fd;
	
	fd = open(line, O_RDONLY);
	if (fd == -1)
		return (PATH_ERR);
	close(fd);
	return (SUCCESS);
}

/*
	In this function we want to safe the texture path given in the scenefile to our data struct.
	- First we have to skip the beginning of the line as there is the identifier (NO , SO ..) and a space
	- than we have to check if there is a valid path
		- there should be word only
		- the path should end with .xpm !!!!! 
		-
*/

t_error	read_texture(char *line, t_identifier identifier, t_data *data)
{
	char *pointer;

	while (line[0] && line[0] == ' ')
		line++;
	if (ft_count_words(line) != 1)
		return (path_error(line, PATH_MULTIPLE_ERR));
	if (check_path(line) == PATH_ERR)
		return (path_error(line, PATH_ERR));
	pointer = set_image_pointer(data, identifier);
	if (!pointer)
		return (ft_putstr_fd("Error\n Missing identifier\n", 2), PATH_ERR);
	pointer = ft_strdup(line);
	if (!pointer)
		return (FATAL_MALOC_ERR);
	return (SUCCESS);
}

