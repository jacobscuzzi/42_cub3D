#include "cub3d.h"

int	ft_count_words(char *line)
{
	int i;
	int words;

	i = 0;
	words = 0;
	while (line[i])
	{
		if (line[i] != ' ')
		{
			words++;
			while (line[i] && line[i] != ' ')
				i++;
		}
		else
			i++;
	}
	return (words);
}

char *set_image_pointer(t_data *data, t_identifier type, char *line)
{
	char *pointer;

	if (type == NORTH)
		pointer = data->graphics.north;
	if (type == SOUTH)
		pointer = data->graphics.south;
	if (type == EAST)
		pointer = data->graphics.east;
	if (type == WEST)
		pointer = data->graphics.west;
	pointer = ft_strdup(line);
	if (!pointer)
		return (NULL);
	return (pointer);
}