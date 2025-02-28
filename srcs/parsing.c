/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:26:12 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/02/28 19:25:26 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_data	*mapping(char *mapfile, int fd)
{
	t_coord	*dimension;
	t_data	*data;
	// /int		check;

	dimension = dimension_check(mapfile);
	if (!dimension)
		return (ft_error(2), free(dimension), NULL);
	data = new_game(dimension);
	if (!data)
		return (ft_error(3), free(dimension), NULL);
	// if (fill_map(data, fd) == 1)
	// 	return (ft_error(7), end_game(data), NULL);
	close(fd);
	// if (wall_check(data) == 0)
	// 	return (ft_error(4), end_game(data), NULL);
	// check = map_check(data);
	// if (check == 0)
	// 	return (ft_error(5), end_game(data), NULL);
	// ft_printf("Characters Validated\n");
	// if (check == -1)
	// 	return (ft_error(6), end_game(data), NULL);
	// ft_printf("Map Validated (Solvable)\n");
	return (data);
}

t_data	*parsing(int argc, char **argv)
{
	t_data *data;
	int		fd;
	int		i;

	if (argc != 2)
		return (ft_error(0), NULL);
	i = ft_strlen(argv[1]) - 1;
	if (!(argv[1][i] == 'b' && argv[1]
		[i - 1] == 'u' && argv[1][i - 2] == 'c' && argv[1][i - 3] == '.'))
		return (ft_error(8), NULL);
	if(argv[1][i - 4] == '/')
		return (ft_error(8), NULL);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_error(1), NULL);
	ft_printf("Map File opened\n");
	data = mapping(argv[1], fd);
	if (data == NULL)
		return (NULL);
	return (data);
}