/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:15:50 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/02/28 19:28:05 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"
void	ft_error(int error_type)
{
	ft_printf("Error\n");
	if (error_type == 0)
		ft_putstr_fd("Number of Arguments Aint right ...\n", 2);
	if (error_type == 1)
		ft_putstr_fd("Mentioned file doesn't open\n", 2);
	if (error_type == 2)
		ft_putstr_fd("Map is not rectangular...\n", 2);
	if (error_type == 3)
		ft_putstr_fd("allocation failed\n", 2);
	if (error_type == 4)
		ft_putstr_fd("Map is missing Walls\n", 2);
	if (error_type == 5)
		ft_putstr_fd("Map has invalid, missing or double* characters\n", 2);
	if (error_type == 6)
		ft_putstr_fd("Map is not solvable\n", 2);
	if (error_type == 7)
		ft_putstr_fd("Error while reading Mapfile\n", 2);
	if (error_type == 8)
		ft_putstr_fd("Invalid Filename. Only type name.ber is exepted\n", 2);
}

void	free_data(t_data *data)
{
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	free_all(data->map, *data->dim);
	free(data->gamer_pos);
	free(data->mlx);
	free(data->dim);
	free(data);
}

void	free_all(char **arr, t_coord dim)
{
	size_t	i;

	i = 0;
	while (i < dim.row)
		free(arr[i++]);
	free(arr);
}

/*
	typedef struct	s_data {
	char	**map;
	t_coord	*dim;
	t_coord	*gamer_pos;
	int		coins;
	void	*mlx;
	void	*mlx_win;
	char	*img;
	char	*addr;
	int		pxl;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_coord	pos;
	char	*gamer_img;
	void	*textures[5];
	int		move_count;

}	t_data;

*/




void	end_game(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free_data(data);
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





// int	main(int argc, char **argv)
// {
// 	int		fd;
// 	t_data	*data;
// 	int		i;

// 	data = parsing(argc, argv);
// 	cub3d(data);
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_data	*data;
	data = parsing(argc, argv);
	//draw_floor(data);
}
/*
void	print_map(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->dim->row)
		ft_printf("%s\n", data->map[i++]);
	return ;
}
*/
