/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:31:23 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/22 17:11:08 by varodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H
# include "cub3d.h"
# include "math.h"
# define WIDTH 1280 // multiple de 64
# define HEIGHT 704 // multiple de 64
# define MINIMAP_WIDTH 200
# define MINIMAP_SCALE 0.2
# define PX_SIZE 64 // Size of each map tile in pixels
# define FOV (PI / 3) // Field of view
# define NUM_RAYS 1280 // 1 ray per pixel (WIDTH)

/*
static const char map[8][9] = {
    "  1111  ",
    "  1001  ",
    "1110011 ",
    " 100001 ",
    "  10N01 ",
    " 110001 ",
    "  1001  ",
    "  1111  "
};
*/

void	ft_putstr_fd(char *s, int fd);
void	ft_error_ray(void);
void	init_mlx(t_data *data);
int end_data(t_data *data);
void	my_pixel_put(int x, int y, t_img *img, int color);
void draw_minimap(t_data *data);
void draw_player(t_data *data, int size);
void draw_ceiling_and_floor(t_data *data);
float init_horizontal_ray(t_data *data, float first_ray, float *rx, float *ry, float *xo, float *yo);
float init_vertical_ray(t_data *data, float first_ray, float *rx, float *ry, float *xo, float *yo);
int get_map_position(t_data *data, float rx, float ry);
float check_wall_hit(t_data *data, float rx, float ry, float px, float py);
float normalize_angle(float angle);
void init_ray_casting(t_data *data, float *first_ray, float *raysfield, int *slice_width);
float fix_fisheye(float distance, float gamer_dir, float ray_angle);
void load_texture(t_data *data, t_texture *texture, char *path);
void draw_wall_slice(t_data *data, int r, float disT, int slice_width, int tex_x);
float check_horizontal_lines(t_data *data, float first_ray, float *hx, float *hy);
float check_vertical_lines(t_data *data, float first_ray, float *vx, float *vy);
void raycasting(t_data *data);
void	cub3d_draw(t_data *data);
int moves(int key, t_data *data);
void	init_events(t_data *data);
int cub_3d(t_data *data);


#endif