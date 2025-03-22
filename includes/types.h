/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:13:23 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/22 16:40:56 by varodrig         ###   ########.fr       */
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
	int	column;
	int	row;
}	t_coord;

typedef struct s_ray
{
    float rx, ry;
    float xo, yo;
    float distance;
    int wall_hit;
} t_ray;

typedef	struct s_rgb
{
	int	red;
	int	green;
	int	blue;
	int	hex;
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

typedef struct s_img
{
    void	*img_ptr;
    char	*pix_ptr;
    int		bpp;
    int		line_len;
    int		endian;
}			t_img;

typedef struct s_texture {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
} t_texture;

typedef enum e_direction
{
    D_NORTH,
    D_SOUTH,
    D_EAST,
    D_WEST
}   t_direction;

typedef struct s_data
{
	char		**map;
	t_coord		map_size;
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_graphics	graphics; //(char *)paths + colors
	t_coord		gamer_pos;
	double		gamer_dir;
	t_texture	north_texture;
    t_texture	south_texture;
    t_texture	east_texture;
    t_texture	west_texture;
	double  px; // player's position in pixels
    double  py;
	double  pdx; // player's position after the next move
    double  pdy;
	t_direction direction;
}	t_data;


#endif