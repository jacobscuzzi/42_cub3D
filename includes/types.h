/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbaumfal <jbaumfal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:13:23 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/18 18:03:47 by jbaumfal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H	
# define TYPES_H

# include "../libft/includes/libft.h"

//NUMBERS

typedef enum e_error
{
	SUCCESS,
	INPUT_ERR,
	OPEN_ERR,
	SCENE_LINE_ERR,
	PATH_ERR,
	PATH_MULTIPLE_ERR,
	RGB_ERR,
	RGB_NUM_ERR,
	MAP_ERR,
	NO_GAMER_ERR,
	MULTIPLE_GAMER_ERR,
	FATAL_MALOC_ERR
}	t_error;

typedef enum e_identifier
{
	NONE,
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
}	t_identifier;

typedef enum e_line
{
	L_EMPTY,
	L_IDENTIFIER,
	L_MAP,
	L_INVALID
}	t_line;



// Structures
typedef struct coordinate
{
	size_t	row;
	size_t	column;
}	t_coord;

typedef	struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_graphics
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	t_rgb	floor;
	t_rgb	ceiling;
}	t_graphics;

typedef struct s_data
{
	char		**map;
	t_coord		map_size;
	void		*mlx;
	void		*mlx_win;
	char		*mlx_img;
	t_graphics	graphics;
	t_coord		gamer_pos;
	double		gamer_dir;
}	t_data;


#endif