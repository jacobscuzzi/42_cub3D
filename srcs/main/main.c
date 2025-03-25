/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:15:50 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/25 18:48:51 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
	This function can hande the things to do 
	when there is an error returned to the main
	For now it only handles the error message

	For some Error types i handle the error messages 
	already in the parsing functions as
	i want to specify the cause for these errors
	
	ERRORS that already print an error message earlier:
		- SCENE_LINE_ERR (in check_line_type_status)
		- PATH_ERR (in)
		- RGB_ERR (in rgb_error)
		- RGB_NUM_ERR (in rgb_error)
*/
void	ft_error(t_error error_type)
{
	if (error_type == INPUT_ERR)
		ft_putstr_fd("Error\nInvalid Input\nNeeds 1 (*.cub) file as input\n", 2);
	if (error_type == OPEN_ERR)
	{
		ft_putstr_fd("Error\nCould not open file.\n", 2);
		ft_putstr_fd("Check name and permissions\n", 2);
	}
	if (error_type == EMPTY_FILE_ERR)
		ft_putstr_fd("Error\nEmpty file\n", 2);
	if (error_type == NO_GAMER_ERR)
		ft_putstr_fd("Error\nNo player found in map\n", 2);
	if (error_type == MULTIPLE_GAMER_ERR)
		ft_putstr_fd("Error\nMultiple players found in map\n", 2);
	if (error_type == MISS_MAP_ERR)
		ft_putstr_fd("Error\nNo map found in scene file\n", 2);
	if (error_type == MAP_LINE_ERR)
		ft_putstr_fd("Error\n Map has to be last element in scenefile\n", 2);
	if (error_type == MAP_EMPTY_LINE_ERR)
		ft_putstr_fd("Error\nEmpty line in map\n", 2);
	if (error_type == MAP_OPEN_ERR)
		ft_putstr_fd("Error\nWatch out! The map has a leak\n", 2);
	if (error_type == FATAL_MALOC_ERR)
		ft_putstr_fd("Error\nMalloc failed\n", 2);
}

void	init_scene_check(t_data *data)
{
	t_scene_check	*scene_check;

	scene_check = &data->scene_check;
	scene_check->north = 0;
	scene_check->south = 0;
	scene_check->west = 0;
	scene_check->east = 0;
	scene_check->floor = 0;
	scene_check->ceiling = 0;
	scene_check->map = false;
	scene_check->map_ended = false;
}

t_data	*init_data(void)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (ft_printf("Error\nMalloc failed\n"), NULL);
	data->map = NULL;
	data->map_size.column = 0;
	data->map_size.row = 0;
	data->gamer_dir = -1;
	data->gamer_pos.row = -1;
	data->gamer_pos.column = -1;
	data->graphics.north = NULL;
	data->graphics.south = NULL;
	data->graphics.west = NULL;
	data->graphics.east = NULL;
	init_scene_check(data);
	return (data);
}

/*
void	print_data(t_data *data)
{
	int	i;

	i = 0;
	printf("Map:\n");
	while (i < data->map_size.row)
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	printf("\n");
	printf("Map Size:\n");
	printf("Row: %d\n", data->map_size.row);
	printf("Column: %d\n", data->map_size.column);
	printf("Player Position:\n");
	printf("Row: %d\n", data->gamer_pos.row);
	printf("Column: %d\n", data->gamer_pos.column);
	printf("Player Direction: %f\n", data->gamer_dir);
	printf("Graphics:\n");
	printf("North: %s\n", data->graphics.north);
	printf("South: %s\n", data->graphics.south);
	printf("West: %s\n", data->graphics.west);
	printf("East: %s\n", data->graphics.east);
	printf("Floor: r:%d g:%d b:%d x:%x\n",
		data->graphics.floor.red, data->graphics.floor.green,
			data->graphics.floor.blue, data->graphics.floor.hex);
	printf("Ceiling: r:%d g:%d b:%d x:%x\n",
		data->graphics.ceiling.red, data->graphics.ceiling.green,
			data->graphics.ceiling.blue, data->graphics.ceiling.hex);
}
*/

int	main(int argc, char **argv)
{
	t_data	*data;
	t_error	status;

	data = init_data();
	if (!data)
		return (1);
	data->map = NULL;
	data->map_size.column = 0;
	data->map_size.row = 0;
	data->gamer_dir = -1;
	data->gamer_pos.row = -1;
	data->gamer_pos.column = -1;
	status = parsing(argc, argv, data);
	if (status != SUCCESS)
		return (clean_up(data), ft_error(status), 1);
	cub_3d(data);
	clean_up(data);
	return (0);
}
