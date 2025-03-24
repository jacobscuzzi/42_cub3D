/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:51:00 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/24 21:58:06 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	Here we check if the character is a valid map character.
	A valid map character is either a '1' '0' 'N' 'S' 'W' 'E'
	The map can also contain spaces so ' ' is also a valid map character.
*/

bool	is_map_char(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == ' ')
		return (true);
	if (c == '\n' || c == '\0' || c == '\t') 
		return (true);
	return (false);
}


/*
	Here we check if the line is an identifier line. 
	An identifier line is a line that starts with an identifier followed by a space.
	This can be "NO" "SO " or "WE " or "EA " or "F " or "C "
	
	We check if the line is at least 3 characters long, that way we dont have to be afraid of errors when stack overflows.
*/

t_identifier is_identifier(char *line)
{
	if (strlen(line) < 3)
		return (NONE);
	while (ft_is_space(line[0]))
		line++;
	if (line[0] == 'N' && line[1] == 'O' && ft_is_space(line[2]))
		return (NORTH);
	if (line[0] == 'S' && line[1] == 'O' && ft_is_space(line[2]))
		return (SOUTH);
	if (line[0] == 'W' && line[1] == 'E' && ft_is_space(line[2]))
		return (WEST);
	if (line[0] == 'E' && line[1] == 'A' && ft_is_space(line[2]))
		return (EAST);
	if (line[0] == 'F' && ft_is_space(line[1]))
		return (FLOOR);
	if (line[0] == 'C' && ft_is_space(line[1]))
		return (CEILING);
	return (NONE);
}

bool	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (ft_is_space(line[i]))
		i++;
	if (line[i] == '\0' || line[i] == '\n')
		return (true);
	return (false);
}


/*
	Here we check if the line is a map line. 
	A map line is a line that contains only valid map characters.
	This check doesnt look if the map is valid, only if the line is completely made out of valid map characters.
*/

bool	check_if_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i])
	{
		if (is_map_char(line[i]) == false)
			return (false);
		i++;
	}
	return (true);
}

/*
	In this function we check each line. 

	If its neither a Empty Line, an identifier Line , or a Map Line, this means it is an invalid line.

	We than print an error message as well as the line that caused the error so the user knows what to change.
*/
t_line check_scenefile_line(char *line)
{
	if (is_empty_line(line) == true)
		return (L_EMPTY);
	if (is_identifier(line) != NONE)
		return (L_IDENTIFIER);
	if (check_if_map(line) == true)
		return (L_MAP);
	ft_putstr_fd("Error\nInvalid line in scene file:\n", 2);
	ft_putstr_fd(line, 2);
	return (L_INVALID);
}