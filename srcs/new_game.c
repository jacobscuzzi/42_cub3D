/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 13:22:04 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/02/28 18:04:02 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
size_t	line_size(char *row)
{
	size_t	i;

	i = 0;
	while (row[i] != '\n' && row[i] != '\0')
		i++;
	return (i);
}

void	column_count(char *row, t_coord	*size)
{
	size->column = line_size(row);
	size->row = 1;
}

int	row_check(t_coord *s, char *row, int fd)
{
	int	error;

	error = 0;
	while (row != NULL)
	{
		if (line_size(row) != s->column)
			error = 1;
		s->row++;
		free(row);
		row = get_next_line(fd);
	}
	return (error);
}

t_coord	*dimension_check(char	*mapfile)
{
	int		fd;
	t_coord	*s;
	char	*row;
	int		error;

	s = (t_coord *)malloc(sizeof(t_coord));
	if (!s)
		return (NULL);
	fd = open(mapfile, O_RDONLY);
	if (fd == -1)
		return (close(fd), free(s), NULL);
	row = get_next_line(fd);
	if (!row)
		return (close(fd), free(s), NULL);
	column_count(row, s);
	free(row);
	row = get_next_line(fd);
	error = row_check(s, row, fd);
	if (error == 1)
		return (close(fd), free(s), NULL);
	else
		return (close(fd), s);
}

char	**init_map(t_coord *dim)
{
	char		**map;
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	map = (char **)malloc(sizeof(char *) * (dim->row));
	if (!map)
		return (NULL);
	while (i < dim->row)
	{
		map[i] = (char *)malloc(sizeof(char) * (dim->column));
		if (!map[i])
			return (free_all(map, *dim), NULL);
		i++;
	}
	return (map);
}

t_data	*new_game(t_coord *dimension)
{
	t_data *(data) = (t_data *)malloc(sizeof (t_data));
	if (!data)
		return (NULL);
	data->map = init_map(dimension);
	if (!(data->map))
		return (free_data(data), NULL);
	ft_printf("map stored in data succesfully\n");
	data->gamer_pos = (t_coord *)malloc(sizeof (t_coord));
	if (!(data->gamer_pos))
		return (NULL);
	data->dim = dimension;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (free_data(data), NULL);
	data->mlx_win = mlx_new_window(data->mlx,
			(data->dim->column) * BLOCK_SIZE,
			(data->dim->row) * BLOCK_SIZE, "Lets play!");
	if (!data->mlx_win)
		return (free_data(data), NULL);
	data->move_count = 0;
	data->pxl = BLOCK_SIZE;
	data->pos.row = 0;
	data->pos.column = 0;
	ft_printf("data allocated succesfully\n");
	return (data);
}
