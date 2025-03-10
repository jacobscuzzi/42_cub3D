/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@42.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:15:50 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/10 03:05:17 by jbaumfal         ###   ########.fr       */
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



int	main(int argc, char **argv)
{
	//t_data	*data;
	t_error	status;

	status = check_input(argc, argv);
	if (status != SUCCESS)
		return (ft_error(status), 1);
	else
		ft_putstr_fd("Valid file\n", 1);
	//data = parsing(argc, argv);
	//cub3d(data);
	return (0);
}