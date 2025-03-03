/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 18:03:16 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/03 15:22:11 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include "../libft/includes/libft.h"
# include <X11/X.h>
# include <X11/keysym.h>

# include "types.h"

# define BLOCK_SIZE 256

# define GAMER 'P'
# define EXIT 'E'
# define COIN 'C'
# define WALL '1'
# define EMPTY '0'

// KEY CODES

# define ESC 65307
# define UP 119
# define LEFT 97
# define DOWN 115
# define RIGHT 100
# define RESTART 114


t_data	*parsing(int argc, char **argv);

// FUNCTIONS FROM OLD SO_LONG PROJECT

void	ft_error(t_error error_type);

int		count_element(t_data *data, char c, char **map);
t_coord	find_element(t_data *data, char c);

int		on_destroy(t_data *data);
int		on_keypress(int keysymm, t_data *data);

void	cub3d(t_data *data);
void	end_game(t_data *data);

// INPUT CHECK
t_error	check_format(int argc, char **argv);
t_error	check_input(int argc, char **argv);

bool	is_map_char(char c);
bool	check_if_map(char *line);

#endif
