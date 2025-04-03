/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:13:23 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/04/03 16:05:52 by varodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include "../libft/includes/libft.h"

typedef enum e_error
{
	SUCCESS,
	INPUT_ERR,
	OPEN_ERR,
	EMPTY_FILE_ERR,
	SCENE_LINE_ERR,
	PATH_ERR,
	PATH_MULTIPLE_ERR,
	PATH_XPM_ERR,
	RGB_ERR,
	RGB_NUM_ERR,
	MAP_OPEN_ERR,
	MAP_LINE_ERR,
	MAP_EMPTY_LINE_ERR,
	NO_GAMER_ERR,
	MISS_MAP_ERR,
	MISS_TEXTURE_ERR,
	MISS_COLOR_ERR,
	MULTIPLE_TEXTURE_ERR,
	MULTIPLE_COLOR_ERR,
	MULTIPLE_GAMER_ERR,
	FATAL_MALOC_ERR
}					t_error;

typedef enum e_identifier
{
	NONE,
	NORTH,
	SOUTH,
	WEST,
	EAST,
	FLOOR,
	CEILING
}					t_identifier;

typedef enum e_line
{
	L_EMPTY,
	L_IDENTIFIER,
	L_MAP,
	L_INVALID
}					t_line;

typedef struct coordinate
{
	int				column;
	int				row;
}					t_coord;

typedef struct s_rgb
{
	int				red;
	int				green;
	int				blue;
	int				hex;
}					t_rgb;

typedef struct s_graphics
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	t_rgb			floor;
	t_rgb			ceiling;
}					t_graphics;

typedef struct s_img
{
	void			*img_ptr;
	char			*pix_ptr;
	int				bpp;
	int				line_len;
	int				endian;
}					t_img;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_texture;

typedef enum e_direction
{
	D_NORTH,
	D_SOUTH,
	D_EAST,
	D_WEST
}					t_direction;

typedef struct s_scene_check
{
	int				north;
	int				south;
	int				west;
	int				east;
	int				floor;
	int				ceiling;
	bool			map;
	bool			map_ended;
}					t_scene_check;

typedef struct s_data
{
	char			**map;
	t_coord			map_size;
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	t_graphics		graphics;
	t_coord			gamer_pos;
	double			gamer_dir;
	t_texture		north_texture;
	t_texture		south_texture;
	t_texture		east_texture;
	t_texture		west_texture;
	double			px;
	double			py;
	double			pdx;
	double			pdy;
	t_direction		direction;
	t_scene_check	scene_check;
}					t_data;

typedef struct s_draw
{
	float			lineh;
	float			lineoffset;
	float			ratio;
	float			tex_pos;
	float			tex_current;
	int				tex_y;
	int				rx;
	int				ry;
	int				slice_width;
}					t_draw;

typedef struct s_ray
{
	float			angle;
	float			field;
	float			dist;
	float			dist_h;
	float			dist_v;
	float			hx;
	float			hy;
	float			vx;
	float			vy;
	int				tex_x;
}					t_ray;

typedef struct s_ray_params
{
	float			rx;
	float			ry;
	float			xo;
	float			yo;
	float			first_ray;
}					t_ray_params;

#endif