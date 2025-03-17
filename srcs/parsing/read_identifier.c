#include "cub3d.h"

int	ft_count_digits(char *line, int i)
{
	int	counter;

	while (line[i] && ft_isdigit(line[i]) == 1)
		counter++;
	return (counter);
}

t_error check_after_last_digit(char *line, int i)
{
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != '\0')
		return (RGB_ERR);
	return (SUCCESS);
}


t_error	check_rgb(char *line)
{
	int	i;
	int	digit_count;
	int	number_count;

	i = 0;
	number_count = 0;
	while (line[i])
	{
		digit_count = ft_count_digits(line, i);
		if (digit_count > 3)
			return (RGB_NUM_ERR);
		if (digit_count == 0)
			return (RGB_ERR);
		number_count++;
		i += digit_count;
		if (number_count == 3)
			return (check_after_last_digit(line, i));
		else
		{
			if (line[i] != ',')
				return (RGB_ERR);
			i++;
		}
	}
	return (RGB_ERR);
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


t_error	read_color(char *line, t_identifier identifier, t_data *data)
{
	int			i;
	int			color;
	t_rgb		rgb;
	t_error		status;

	while (line[0] && line[0] == ' ')
		line++;
	if (!line[0])
		return (RGB_ERR);
	status = check_rgb(line);
	if (status != SUCCESS)
		return (status);
	rgb.red = ft_atoi(line);
	line += ft_count_digits(line, 0) + 1;
	rgb.green = ft_atoi(line);
	line += ft_count_digits(line, 0) + 1;
	rgb.blue = ft_atoi(line);
	if (rgb.red > 255 || rgb.green > 255 || rgb.blue > 255)
		return (RGB_NUM_ERR);
	if (identifier == FLOOR)
		data->graphics.floor = rgb;
	else
		data->graphics.ceiling = rgb;
	return (SUCCESS);
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
	t_error	status;
	char *pointer;

	while (line[0] && line[0] == ' ')
		line++;
	if (ft_count_words(line) != 1)
		return (PATH_ERR);
	if (check_path == PATH_ERR)
		return (PATH_ERR);
	pointer = set_image_pointer(data, identifier);
	if (!pointer)
		return (PATH_ERR);
	pointer = ft_strdup(line);
	if (!pointer)
		return (FATAL_ERR);
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