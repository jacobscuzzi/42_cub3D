/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:15:50 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/18 17:56:31 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

/*
	This function can hande the things to do when there is an error returned to the main
	For now it only handles the error message

	For some Error types i handle the error messages already in the parsing functions as
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
		ft_putstr_fd("Error\nCould not open file. Check name and permissions\n", 2);
	if (error_type == NO_GAMER_ERR)
		ft_putstr_fd("Error\nNo player found in map\n", 2);
	if (error_type == MULTIPLE_GAMER_ERR)
		ft_putstr_fd("Error\nMultiple players found in map\n", 2);
}

void	end_game(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	exit(1);
}

void	cub3d(t_data *data)
{
	mlx_hook(data->mlx_win, KeyRelease, KeyReleaseMask,
		&on_keypress, data);
	mlx_hook(data->mlx_win, DestroyNotify, StructureNotifyMask,
		&on_destroy, data);
	mlx_loop(data->mlx);
	exit(0);
	return ;
}

/*
	DATA TYPE:

	typedef struct s_data
	{
		char		**map;
		t_coord		map_size;
		void		*mlx;
		void		*mlx_win;
		t_graphics	graphics;
	}	t_data;
*/

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
	data->mlx = mlx_init();
	if (!data->mlx)
		return (ft_printf("Error\n mlx_init failed\n"), NULL);
	data->mlx_win = mlx_new_window(data->mlx, 640, 480, "Hello world!");
	if (!data->mlx_win)
		return (ft_printf("Error\nmlx_new_window failed\n"), NULL);
	return (data);
}


int	main(int argc, char **argv)
{
	t_data	*data;
	t_error	status;

	data = init_data();
	if (!data)
		return (1);
	status = parsing(argc, argv, data);
	if (status != SUCCESS)
		return (ft_error(status), 1);
	else
		ft_putstr_fd("Succesful Parcing\n", 1);
	//cub3d(data);
	return (0);
}