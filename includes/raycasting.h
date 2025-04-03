/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:31:23 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/04/03 16:23:00 by varodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTING_H
# define RAYCASTING_H
# include "cub3d.h"
# include "math.h"
# include "types.h"
# define WIDTH 1280
# define HEIGHT 704
# define PX_SIZE 64
# define NUM_RAYS 1280
# define MINI_SQUARE_SIZE 4

void		draw_minimap(t_data *data);
void		draw_square(t_data *data, int x, int y, int color);
void		draw_player(t_data *data, int size);
void		draw_ceiling_and_floor(t_data *data);
void		cub3d_draw(t_data *data);

void		init_mlx(t_data *data);
int			end_data(t_data *data);
void		load_texture(t_data *data, t_texture *texture, char *path);
void		init_parameters(t_data *data);

void		right_move(t_data *data);
void		left_move(t_data *data);
void		w_move(t_data *data);
void		s_move(t_data *data);
void		a_move(t_data *data);
void		d_move(t_data *data);

t_texture	*get_wall_texture(t_data *data);
void		init_draw_params(t_draw *d, float disT);
void		draw_texture_line(t_data *data, t_draw *d, int tex_x);
void		draw_wall_slice(t_data *data, int r, float disT, int tex_x);
float		set_wall_direction(t_data *data, float dist_h, float dist_v,
				t_ray *ray);
void		init_ray_casting(t_data *data, t_ray *ray, float *raysfield);
void		raycasting(t_data *data);

float		init_vertical_ray(t_data *data, t_ray_params *ray_params);
float		init_horizontal_ray(t_data *data, t_ray_params *ray_params);
float		check_horizontal_lines(t_data *data, float first_ray, float *hx,
				float *hy);
float		check_vertical_lines(t_data *data, float first_ray, float *vx,
				float *vy);

int			cub_3d(t_data *data);
void		init_events(t_data *data);
int			moves(int key, t_data *data);
float		fix_fisheye(float distance, float gamer_dir, float ray_angle);
float		normalize_angle(float angle);
int			get_map_position(t_data *data, float rx, float ry);
void		ft_putstr_fd(char *s, int fd);
void		ft_error_ray(void);
int			end_data_error(t_data *data);
void		my_pixel_put(int x, int y, t_img *img, int color);

#endif