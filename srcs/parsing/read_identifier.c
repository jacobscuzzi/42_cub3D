#include "cub3d.h"

t_error	check_rgb(char *line)
{
	
}


t_error check_path(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (SCENE_LINE_ERR);
	return (SUCCESS);
}

t_error	read_color(char *line, t_identifier identifier, t_data *data)
{
	int		i;
	int		color;
	t_rgb	*rgb;

	i = 2;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (SCENE_LINE_ERR);
	/*  */
}


/*
	In this function we want to safe the texture path given in the scenefile to our data struct.
	- First we have to skip the beginning of the line as there is the identifier (NO , SO ..) and a space
	- than we have to check if there is a valid path
		- there should be word only
		- the path should end with .xpm
		-
*/

t_error	read_texture(char *line, t_identifier identifier, t_data *data)
{
	char	*path;
	int		i;

	i = 3;
	while (line[i] && line[i] == ' ')
		i++;
	
}

t_error read_identifier(char *line, t_data *data)
{
    t_identifier    identifier;
	t_error			status;

    identifier = is_identifier(line);
	if (identifier == NORTH || identifier == SOUTH || identifier == WEST || identifier == EAST)
		status = read_texture(line, identifier, data);
	else
		status = read_color(line, identifier, data);
	return (status);
    
}