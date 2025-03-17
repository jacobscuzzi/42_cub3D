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

char *set_image_pointer(t_data *data, t_identifier type)
{
	if (type == NORTH)
		return (data->graphics.north);
	if (type == SOUTH)
		return (data->graphics.south);
	if (type == EAST)
		return (data->graphics.east);
	if (type == WEST)
		return (data->graphics.west);
	return (NULL);
}