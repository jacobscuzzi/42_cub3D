#include "cub3d.h"

bool	is_surrounded(t_data *data, int row, int column)
{
	if (row == 0 || row == data->map_size.row)
		return (false);
	if (column == 0 || column == data->map_size.column)
		return (false);
	if (data->map[row - 1][column] == ' ' || data->map[row + 1][column] == ' ')
		return (false);
	if (data->map[row][column - 1] == ' ' || data->map[row][column + 1] == ' ')
		return (false);
	return (true);
}

t_error map_check(t_data *data)
{
	int row;
	int column;

	row = 0;
	while (row < data->map_size.row)
	{
		column = 0;
		while (column < data->map_size.column)
		{
			if (data->map[row][column] == '0' && !is_surrounded(data, row, column))
				return (MAP_ERR);
			column++;
		}
		row++;
	}
}
