/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:13:23 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/24 15:41:59 by jbaumfal         ###   ########.fr       */
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
	MISS_MAP_ERR,
	MISS_TEXTURE_ERR,
	MISS_COLOR_ERR,
	MULTIPLE_TEXTURE_ERR,
	MULTIPLE_COLOR_ERR,
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
	int	hex; //parsing
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
    void	*img_ptr; //init_mlx
    char	*pix_ptr; //init_mlx
    int		bpp;
    int		line_len;
    int		endian;
}			t_img;

typedef struct s_texture {
    void    *img;  //load_texture
    char    *addr;  //load_texture
    int     bits_per_pixel;  //load_texture
    int     line_length; //load_texture
    int     endian;  //load_texture
    int     width; //load_texture
    int     height; //load_texture
} t_texture;

typedef enum e_direction
{
    D_NORTH,
    D_SOUTH,
    D_EAST,
    D_WEST
}   t_direction;

typedef struct s_scene_check
{
	int			north;
	int			south;
	int			west;
	int			east;
	int			floor;
	int			ceiling;
	bool			map;
}	t_scene_check;

typedef struct s_data
{
	char		**map; //parsing
	t_coord		map_size; //parsing
	void		*mlx_ptr; //init_mlx
	void		*win_ptr; //init_mlx
	t_img		img; 
	t_graphics	graphics; //parsing //(char *)paths + colors
	t_coord		gamer_pos; //parsing
	double		gamer_dir; //parsing
	t_texture	north_texture; //load_texture
    t_texture	south_texture; //load_texture
    t_texture	east_texture; //load_texture
    t_texture	west_texture; //load_texture
	double  px; //init_mlx // player's position in pixels
    double  py; //init_mlx
	double  pdx; //init_mlx // player's position after the next move
    double  pdy; //init_mlx
	t_direction direction; //raycasting
  t_scene_check	scene_check;
}	t_data;


#endif

//r
//first_ray
//raysfield
//slice_width
//vx
//vy
//tex_x

//dof
//wall_distance
//ry
//rx
//aTan
//yo
//xo
//disV
//vx
//vy
//hx
//hy

//mx
//my

//ca

//draw_wall_slice(data, r, wall_distance, slice_width, tex_x);
//lineH
//lineO
//ratio
//tex_pos
//i
//j
//tex_current
//tex_y
//current_texture
//color