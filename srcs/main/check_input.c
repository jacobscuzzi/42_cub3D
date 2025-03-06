/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:40:38 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/06 17:14:20 by jbaumfal         ###   ########.fr       */
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



t_error	check_scene_file(char *path)
{
	int				fd;
	char			*line;
	t_error			status;
	t_line_check	line_type;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (OPEN_ERR);
	line = NULL;
	line = get_next_line(fd);
	if (!line)
		return (FATAL_ERROR);
	while (line)
	{
		line_type = check_line(line);
		if (line_type == L_INVALID)
			return (SCENE_LINE_ERR);
		free(line);
		line = NULL;
		line = get_next_line(fd);
	}
	status = check_map(fd, line);
	close(fd);
	return (status);
}

t_error	check_input(int argc, char **argv)
{
	t_error	status;

	status = check_format(argc, argv);
	if (status != SUCCESS)
		return (status);
	status = check_scene_file(argv[1]);
	return (status);
}