/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:15:50 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/17 04:46:06 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	ft_error(t_error error_type)
{
	if (error_type == INPUT_ERR)
		ft_putstr_fd("Error\nInvalid Input\nNeeds 1 (*.cub) file as input", 2);
	if (error_type == OPEN_ERR)
		ft_putstr_fd("Error\nCould not open file. Check name and permissions", 2);
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
	status = parsing(argc, argv);
	if (status != SUCCESS)
		return (ft_error(status), 1);
	else
		ft_putstr_fd("Succesful Parcing\n", 1);
	//data = parsing(argc, argv);
	//cub3d(data);
	return (0);
}