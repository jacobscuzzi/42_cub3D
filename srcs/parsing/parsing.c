/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:26:12 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/12 15:09:58 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_error read_map(char *line, t_data *data, int fd)
{

}

t_error read_scenefile(int fd, t_data *data)
{
    t_error      status;
    char         *line;
    t_line_check line_type;

    line = get_next_line(fd);
    while (line)
    {
        line_type = check_scenefile_line(line);
        if (line_type == L_IDENTIFIER)
            status = read_identifier(line, data);
        else if (line_type == L_MAP)
            status = read_map(line, data, fd);
        else if (line_type == L_EMPTY)
            status = SUCCESS;
        else if (line_type == L_INVALID)
            status = SCENE_LINE_ERR;
        if (status != SUCCESS)
            return (free(line), status);
        free(line);
        line = get_next_line(fd);
    }
    return status;
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
    status = check_scene_file(argv[1]);
    if (status != SUCCESS)
		return (status);
    else
        ft_putstr_fd("Valid Scenefile\n", 1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (OPEN_ERR);
    status = read_scenefile(fd, data);
    return (status);
}
