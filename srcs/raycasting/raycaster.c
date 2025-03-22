/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varodrig <varodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:30:39 by jbaumfal          #+#    #+#             */
/*   Updated: 2025/03/22 17:14:58 by varodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
typedef struct s_ray
{
    float rx, ry;
    float xo, yo;
    float distance;
    int wall_hit;
} t_ray;

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

typedef struct s_raycaster
{
    void	*mlx_ptr;
    void	*win_ptr;
    t_img	img;
    int     background_color;
    int     graphics->ceiling;
    int     graphics->floor;
    int     wall_color;
    double  px; // Position du joueur
    double  py; // Position du joueur
    double  gamer_dir; // Orientation du joueur en radians
    double  pdx; // Projection du prochain mouvement
    double  pdy;
    int     col; 
    int     lines;
    t_texture north_texture;
    t_texture south_texture;
    t_texture east_texture;
    t_texture west_texture;
    t_direction direction;
}   t_data;
*/

void	ft_putstr_fd(char *s, int fd)
{
    int	i;

    if (NULL == s || fd < 0)
        return ;
    i = 0;
    while (s[i])
    {
        write(fd, &s[i], 1);
        i++;
    }
}

void	ft_error_ray(void)
{
    ft_putstr_fd("malloc failed\n", STDERR_FILENO);
    exit(1);
}

void	init_mlx(t_data *data)
{
    data->mlx_ptr = mlx_init();
    if (!data->mlx_ptr)
        ft_error_ray();
    data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT,
            "data");
    if (!data->win_ptr)
    {
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
        ft_error_ray();
    }
    data->img.img_ptr = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
    if (!data->img.img_ptr)
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
        ft_error_ray();
    }
    data->img.pix_ptr = mlx_get_data_addr(data->img.img_ptr,
            &data->img.bpp, &data->img.line_len, &data->img.endian);
    load_texture(data, &data->north_texture, data->graphics.north);
    load_texture(data, &data->south_texture, data->graphics.south);
    load_texture(data, &data->west_texture, data->graphics.west);
    load_texture(data, &data->east_texture, data->graphics.east);
    //data->background_color = 0xA9A9A9;
    data->px = (data->gamer_pos.column) * PX_SIZE + (PX_SIZE / 2); //from map index to position in pixel
    data->py = (data->gamer_pos.row) * PX_SIZE + (PX_SIZE / 2); 
    data->pdx = cos(data->gamer_dir) * 5; //cos(0)=1
    data->pdy = sin(data->gamer_dir) * 5; //sin(0)=0
}

int end_data(t_data *data)
{
    if (data->north_texture.img)
        mlx_destroy_image(data->mlx_ptr, data->north_texture.img);
    if (data->south_texture.img)
        mlx_destroy_image(data->mlx_ptr, data->south_texture.img);
    if (data->east_texture.img)
        mlx_destroy_image(data->mlx_ptr, data->east_texture.img);
    if (data->west_texture.img)
        mlx_destroy_image(data->mlx_ptr, data->west_texture.img);
    if (data->img.img_ptr)
        mlx_destroy_image(data->mlx_ptr, data->img.img_ptr);
    if (data->win_ptr)
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
    if (data->mlx_ptr)
    {
        mlx_destroy_display(data->mlx_ptr);
        free(data->mlx_ptr);
    }
    
    exit(0);
}

//TODO:e
void	my_pixel_put(int x, int y, t_img *img, int color)
{
    int	offset;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        offset = (y * img->line_len) + (x * (img->bpp / 8));
        *(unsigned int *)(img->pix_ptr + offset) = color;
    }
}

/*
//Bresenham algorithm (not mine) //TODO: delete or change
void draw_line(t_img *img, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0); // Différence absolue en x
    int dy = abs(y1 - y0); // Différence absolue en y
    int sx = (x0 < x1) ? 1 : -1; // Direction du pas en x
    int sy = (y0 < y1) ? 1 : -1; // Direction du pas en y
    int err = dx - dy; // Erreur initiale

    while (1)
    {
        my_pixel_put(x0, y0, img, color); // Dessiner le pixel à la position actuelle
        if (x0 == x1 && y0 == y1) // Si on a atteint le point final, sortir de la boucle
            break;
        int e2 = err * 2; // Double de l'erreur
        if (e2 > -dy)
        {
            err -= dy; // Ajuster l'erreur
            x0 += sx; // Avancer en x
        }
        if (e2 < dx)
        {
            err += dx; // Ajuster l'erreur
            y0 += sy; // Avancer en y
        }
    }
}
*/

void draw_minimap(t_data *data)
{
    int x = 0;
    int y = 0;
    int xo, yo;
    int color;
    // Calculer la taille d'une case en fonction de MINIMAP_WIDTH
    int square_size = MINIMAP_WIDTH / data->map_size.column;  // Divise la largeur par le nombre de colonnes
 
    while (y < data->map_size.row)
    {
        x = 0;
        while (x < data->map_size.column)
        {
            if(data->map[y][x] == '1')
                color = 0xFFFFFF;
            else
                color = 0x000000;
            
            xo = x * square_size;
            yo = y * square_size;

            int i = xo;
            while (i < xo + square_size)
            {
                int j = yo;
                while (j < yo + square_size)
                {
                    my_pixel_put(i, j, &data->img, color);
                    j++;
                }
                i++;
            }
            x++;
        }
        y++;
    }
}

void draw_player(t_data *data, int size)
{
    int square_size = MINIMAP_WIDTH / data->map_size.column;
    // Convertir la position du joueur à l'échelle de la minimap
    int center_x = (data->px / PX_SIZE) * square_size;
    int center_y = (data->py / PX_SIZE) * square_size;
    int red = 0xFF0000;
    // Taille du joueur proportionnelle aux cases de la minimap
    int scaled_size = size * (square_size / PX_SIZE);
    int x = -scaled_size/2;
    int y;

    while (x <= scaled_size/2)
    {
        y = -scaled_size/2;
        while (y <= scaled_size/2)
        {
            my_pixel_put(center_x + x, center_y + y, &data->img, red);
            y++;
        }
        x++;
    }
}

//TODO: des le debut ou juste pour minimap ?
/*
void    draw_background(t_data *data) 
{
    int	x;
    int	y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_pixel_put(x, y, &data->img, data->background_color);
            x++;
        }
        y++;
    }
}
*/

void draw_ceiling_and_floor(t_data *data)
{
    int x;
    int y;
    
    x= 0;
    while (x < WIDTH)
    {
        y = 0;
        while (y < HEIGHT)
        {
            if (y < HEIGHT/2)
                my_pixel_put(x, y, &data->img, data->graphics.ceiling.hex);
            else
                my_pixel_put(x, y, &data->img, data->graphics.floor.hex);
            y++;
        }
        x++;
    }
}

float init_horizontal_ray(t_data *data, float first_ray, float *rx, float *ry, float *xo, float *yo)
{
    float aTan = -1 / tan(first_ray);
    
    if (first_ray == 0 || first_ray == PI)
        return (8);  // Skip horizontal checks
    if (first_ray > PI)  // Looking up
    {
        *ry = (floor(data->py / PX_SIZE) * PX_SIZE) - 0.0001;
        *rx = (data->py - *ry) * aTan + data->px;
        *yo = -PX_SIZE;
        *xo = -(*yo) * aTan;
    }
    else  // Looking down
    {
        *ry = (floor(data->py / PX_SIZE) * PX_SIZE) + PX_SIZE;
        *rx = (data->py - *ry) * aTan + data->px;
        *yo = PX_SIZE;
        *xo = -(*yo) * aTan;
    }
    return (0);
}

float init_vertical_ray(t_data *data, float first_ray, float *rx, float *ry, float *xo, float *yo)
{
    float nTan = -tan(first_ray);
    
    if (first_ray == PI/2 || first_ray == 3*PI/2)
        return (8);  // Skip vertical checks
    if (first_ray > PI/2 && first_ray < 3*PI/2)  // Looking left
    {
        *rx = (floor(data->px/PX_SIZE) * PX_SIZE) - 0.0001;
        *ry = (data->px - *rx) * nTan + data->py;
        *xo = -PX_SIZE;
        *yo = -(*xo) * nTan;
    }
    else  // Looking right
    {
        *rx = (floor(data->px/PX_SIZE) * PX_SIZE) + PX_SIZE;
        *ry = (data->px - *rx) * nTan + data->py;
        *xo = PX_SIZE;
        *yo = -(*xo) * nTan;
    }
    return (0);
}

int get_map_position(t_data *data, float rx, float ry)
{
    int mx = (int)(rx) / PX_SIZE;
    int my = (int)(ry) / PX_SIZE;
    
    if (mx >= 0 && mx < 8 && my >= 0 && my < 8)
    {
        if (data->map[my][mx] == '1')
            return (1);
    }
    return (0);
}

float check_wall_hit(t_data *data, float rx, float ry, float px, float py)
{
    int mx = (int)(rx) / PX_SIZE;
    int my = (int)(ry) / PX_SIZE;
    if (mx >= 0 && mx < 8 && my >= 0 && my < 8 && data->map[my][mx] == '1')
        return (sqrt((rx-px)*(rx-px) + (ry-py)*(ry-py)));
    return (1000000);
}

float normalize_angle(float angle)
{
    while (angle < 0) 
        angle += 2 * PI;
    while (angle > 2 * PI)
        angle -= 2 * PI;
    return angle;
}

void init_ray_casting(t_data *data, float *first_ray, float *raysfield, int *slice_width)
{
    *raysfield = FOV / NUM_RAYS;
    *first_ray = normalize_angle(data->gamer_dir - FOV/2);
    *slice_width = WIDTH / NUM_RAYS;
}

float fix_fisheye(float distance, float gamer_dir, float ray_angle)
{
    float ca = normalize_angle(gamer_dir - ray_angle);
    return distance * cos(ca);
}

void load_texture(t_data *data, t_texture *texture, char *path)
{
    texture->img = mlx_xpm_file_to_image(data->mlx_ptr, path, 
                                        &texture->width, &texture->height);
    if (!texture->img)
        ft_error_ray();
    texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
                                     &texture->line_length, &texture->endian);
}

void draw_wall_slice(t_data *data, int r, float disT, int slice_width, int tex_x)
{
    float lineH = (PX_SIZE * HEIGHT) / disT;
    float lineO = (HEIGHT - lineH) / 2;
    float ratio = 64.0 / lineH; //image size / wall height 
    // step = 1, 1 texture pixel -> 1 wall pixel
    // step = 0.5, 1 texture pixel -> 2 wall pixel
    // step = 2, 2 texture pixels -> 1 wall pixel
    float tex_pos = 0;

    if (lineH > HEIGHT)
    {
        tex_pos = (lineH - HEIGHT) / 2.0 * ratio;
        lineH = HEIGHT;
        lineO = 0;
    }

    int i = 0;
    while (i < slice_width)
    {
        int j = 0;
        float tex_current = tex_pos;
        while (j < lineH)
        {
            int tex_y = (int)tex_current % 64;
            t_texture *current_texture;

            if (data->direction == 1)
                current_texture = &data->north_texture;
            else if (data->direction == 2)
                current_texture = &data->south_texture;
            else if (data->direction == 3)
                current_texture = &data->west_texture;
            else
                current_texture = &data->east_texture;

            int color = *(int*)(current_texture->addr + 
                (tex_y * current_texture->line_length + 
                tex_x * (current_texture->bits_per_pixel / 8)));
            my_pixel_put(r * slice_width + i, j + lineO, &data->img, color);
            tex_current += ratio;
            j++;
        }
        i++;
    }
}

float check_horizontal_lines(t_data *data, float first_ray, float *hx, float *hy)
{
    float rx, ry, xo, yo;
    int dof = 0;
    float wall_distance = 1000000;

    dof = init_horizontal_ray(data, first_ray, &rx, &ry, &xo, &yo);
    while (dof < 8)
    {
        if (get_map_position(data, rx, ry))
        {
            wall_distance = check_wall_hit(data, rx, ry, data->px, data->py);
            if (wall_distance < 1000000)
            {
                *hx = rx;
                *hy = ry;
                return (wall_distance);
            }
        }
        rx += xo;
        ry += yo;
        dof++;
    }
    return (wall_distance);
}

float check_vertical_lines(t_data *data, float first_ray, float *vx, float *vy)
{
    float rx, ry, xo, yo;
    int dof = 0;
    float disV = 1000000;

    dof = init_vertical_ray(data, first_ray, &rx, &ry, &xo, &yo);
    while (dof < 8)
    {
        if (get_map_position(data, rx, ry))
        {
            disV = check_wall_hit(data, rx, ry, data->px, data->py);
            if (disV < 1000000)
            {
                *vx = rx;
                *vy = ry;
                return (disV);
            }
        }
        rx += xo;
        ry += yo;
        dof++;
    }
    return (disV);
}

void raycasting(t_data *data)
{
    float raysfield, first_ray;  
    int slice_width;
    float hx, hy, vx, vy;
    // hx, hy: coordinates of the wall impact point for horizontal intersections
    // vx, vy: coordinates of the wall impact point for vertical intersections
    float wall_distance, disV;
    int r = 0;
    int tex_x;

    draw_ceiling_and_floor(data);
    init_ray_casting(data, &first_ray, &raysfield, &slice_width);

    while (r < NUM_RAYS)
    {
        wall_distance = check_horizontal_lines(data, first_ray, &hx, &hy);
        disV = check_vertical_lines(data, first_ray, &vx, &vy);

        if (disV < wall_distance)
        {
            // vertical walls
            if (first_ray > PI/2 && first_ray < 3*PI/2)
            {
                data->direction = 4;  // West
                tex_x = (int)vy % 64;  // Position x dans la texture
            }
            else
            {
                data->direction = 3;  // D_EAST
                tex_x = (int)vy % 64;
            }
            wall_distance = disV;
        }
        else
        {
            // horizontal walls
            if (first_ray > PI)
            {
                tex_x = (int)hx % 64;  // Position x dans la texture pour mur nord
                data->direction = 1;   // Flag pour indiquer un mur nord
            }
            else
            {
                tex_x = (int)hx % 64;  // D_SOUTH
                data->direction = 2;
            }
        }
        wall_distance = fix_fisheye(wall_distance, data->gamer_dir, first_ray);
        draw_wall_slice(data, r, wall_distance, slice_width, tex_x);

        first_ray = normalize_angle(first_ray + raysfield);
        r++;
    }
}

void	cub3d_draw(t_data *data)
{
    //draw_background(data);
    raycasting(data);
    draw_minimap(data);
    draw_player(data, 2);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
        data->img.img_ptr, 0, 0);
    /*
    int		img_width;
	int		img_height;

    data->img.img_ptr = mlx_xpm_file_to_image(data->mlx_ptr,
        "./wall_lvl0.xpm", &img_width, &img_height);;
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
        data->img.img_ptr, 700, 200);
    */
}

int moves(int key, t_data *data)
{
    if (key == XK_Escape)
        end_data(data);
    else if (key == XK_Right) // Turn right 
    {
        data->gamer_dir += 0.1;
        if (data->gamer_dir > 2*PI)
            data->gamer_dir -= 2*PI;
        data->pdx = cos(data->gamer_dir) * 5;
        data->pdy = sin(data->gamer_dir) * 5;
    }
    else if (key == XK_Left) // Turn left
    {
        data->gamer_dir -= 0.1;
        if (data->gamer_dir < 0)
            data->gamer_dir += 2*PI;
        data->pdx = cos(data->gamer_dir) * 5;
        data->pdy = sin(data->gamer_dir) * 5;
    }  
    else if (key == XK_w) // Avancer
    {
        double new_px = data->px + data->pdx;
        double new_py = data->py + data->pdy;
        int map_x = (int)(new_px / PX_SIZE);
        int map_y = (int)(new_py / PX_SIZE);
        if(data->map[map_y][map_x] == '0' || data->map[map_y][map_x] == 'N')
        {
            data->px += data->pdx;
            data->py += data->pdy;
            //printf("x = %f y = %f pa = %f\n\n", data->px, data->py, data->gamer_dir);
        }  
    }
    else if (key == XK_s) // Reculer
    {
        double new_px = data->px - data->pdx;
        double new_py = data->py - data->pdy;
        int map_x = (int)(new_px / PX_SIZE);
        int map_y = (int)(new_py / PX_SIZE);
        if(data->map[map_y][map_x] == '0' || data->map[map_y][map_x] == 'N')
        {
            data->px -= data->pdx;
            data->py -= data->pdy;
            //printf("x = %f y = %f pa = %f\n\n", data->px, data->py, data->gamer_dir);
        }
    }
    else if (key == XK_a) // se decaler a gauche
    {
        double new_px = data->px + cos(data->gamer_dir - PI/2) * 5;
        double new_py = data->py + sin(data->gamer_dir - PI/2) * 5;
        int map_x = (int)(new_px / PX_SIZE);
        int map_y = (int)(new_py / PX_SIZE);
        if(data->map[map_y][map_x] == '0' || data->map[map_y][map_x] == 'N')
        {
            data->px = new_px;
            data->py = new_py;
            //printf("x = %f y = %f pa = %f\n\n", data->px, data->py, data->gamer_dir);
        }
    }
    else if (key == XK_d) // se decaler a droite
    {
        double new_px = data->px + cos(data->gamer_dir + PI/2) * 5;
        double new_py = data->py + sin(data->gamer_dir + PI/2) * 5;
        int map_x = (int)(new_px / PX_SIZE);
        int map_y = (int)(new_py / PX_SIZE);
        if(data->map[map_y][map_x] == '0' || data->map[map_y][map_x] == 'N')
        {
            data->px = new_px;
            data->py = new_py;
            //printf("x = %f y = %f pa = %f\n\n", data->px, data->py, data->gamer_dir);
        }
    }
    cub3d_draw(data);
    return (0);
}

void	init_events(t_data *data)
{
    mlx_hook(data->win_ptr,KeyPress, KeyPressMask, &moves, data);
    mlx_hook(data->win_ptr, DestroyNotify, 0, end_data, data);
}

int cub_3d(t_data *data)
{
    init_mlx(data);
    cub3d_draw(data);
    init_events(data);
    mlx_loop(data->mlx_ptr);
	return (SUCCESS);
}
