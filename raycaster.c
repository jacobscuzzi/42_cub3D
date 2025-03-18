#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h> // Pour les fonctions trigonométriques
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# define WIDTH 1280 // multiple de 64
# define HEIGHT 704 // multiple de 64
# define MINIMAP_WIDTH 200
# define MINIMAP_SCALE 1
# define PX_SIZE 64
# define PI 3.141592
# define FOV (PI / 3) // Field of view
# define NUM_RAYS 1280 // 1 ray per pixel (WIDTH)
# define ROW 4
# define COL 4

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

typedef struct s_raycaster
{
    void	*mlx_ptr;
    void	*win_ptr;
    t_img	img;
    int     background_color;
    int     ceiling_color;
    int     floor_color;
    int     wall_color;
    double  px; // Position du joueur
    double  py; // Position du joueur
    double  player_angle; // Orientation du joueur en radians
    double  pdx; // Projection du prochain mouvement
    double  pdy;
    int     col; 
    int     lines;
}   t_raycaster;

void init_ray_casting(t_raycaster *cub3d, float *first_ray, float *raysfield, int *slice_width);
void cast_horizontal_ray(t_raycaster *cub3d, float ray_angle, t_ray *ray);
void cast_vertical_ray(t_raycaster *cub3d, float ray_angle, t_ray *ray);
void draw_wall_slice(t_raycaster *cub3d, int ray_num, float distance, int slice_width);
float check_horizontal_lines(t_raycaster *cub3d, float ray_angle, float *hx, float *hy);
float check_vertical_lines(t_raycaster *cub3d, float ray_angle, float *vx, float *vy);
void draw_wall_slice(t_raycaster *cub3d, int r, float disT, int slice_width);

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

static void	ft_error(void)
{
    ft_putstr_fd("malloc failed\n", STDERR_FILENO);
    exit(1);
}

void	init_mlx(t_raycaster *cub3d)
{
    cub3d->mlx_ptr = mlx_init();
    if (!cub3d->mlx_ptr)
        ft_error();
    cub3d->win_ptr = mlx_new_window(cub3d->mlx_ptr, WIDTH, HEIGHT,
            "cub3D");
    if (!cub3d->win_ptr)
    {
        mlx_destroy_display(cub3d->mlx_ptr);
        free(cub3d->mlx_ptr);
        ft_error();
    }
    cub3d->img.img_ptr = mlx_new_image(cub3d->mlx_ptr, WIDTH, HEIGHT);
    if (!cub3d->img.img_ptr)
    {
        mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
        mlx_destroy_display(cub3d->mlx_ptr);
        free(cub3d->mlx_ptr);
        ft_error();
    }
    cub3d->img.pix_ptr = mlx_get_data_addr(cub3d->img.img_ptr,
            &cub3d->img.bpp, &cub3d->img.line_len, &cub3d->img.endian);
    cub3d->background_color = 0xA9A9A9;
    cub3d->ceiling_color = 0x4A4A4A;
    cub3d->floor_color = 0x696969;
    cub3d->px = ROW * PX_SIZE + (PX_SIZE / 2); //TODO: parameter from parsing
    cub3d->py = COL * PX_SIZE + (PX_SIZE / 2); 
    cub3d->col = 8;
    cub3d->lines = 9;
    cub3d->player_angle = 3*PI/2; //looking up
    cub3d->pdx = cos(cub3d->player_angle) * 5; //cos(0)=1
    cub3d->pdy = sin(cub3d->player_angle) * 5; //sin(0)=0
}

int	end_cub3d(t_raycaster *cub3d)
{
    mlx_destroy_image(cub3d->mlx_ptr, cub3d->img.img_ptr);
    mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
    mlx_destroy_display(cub3d->mlx_ptr);
    free(cub3d->mlx_ptr);
    exit(0);
}

//TODO:e
static void	my_pixel_put(int x, int y, t_img *img, int color)
{
    int	offset;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        offset = (y * img->line_len) + (x * (img->bpp / 8));
        *(unsigned int *)(img->pix_ptr + offset) = color;
    }
}

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

void    draw_map(t_raycaster *cub3d)
{
    int x = 0;
    int y = 0;
    int xo, yo;
    int color;
    int scale = PX_SIZE * MINIMAP_SCALE;
 
    while (y < cub3d->lines)
    {
        x = 0;
        while (x < cub3d->col)
        {
            if(map[y][x] == '1')
                color = 0xFFFFFF;
            else
                color = 0x000000;
            
            xo = x * scale;
            yo = y * scale;

            int i = xo;
            while (i < xo + (scale))
            {
                int j = yo;
                while (j < yo + (scale))
                {
                    my_pixel_put(i, j, &cub3d->img, color);
                    j++;
                }
                i++;
            }
            x++;
        }
        y++;
    }
}

void draw_player(t_raycaster *cub3d, int size)
{
    int center_x = cub3d->px;
    int center_y = cub3d->py;
    int red = 0xFF0000;
    int x = -size/2;
    int y;

    while (x <= size/2)
    {
        y = -size/2;
        while (y <= size/2)
        {
            my_pixel_put((center_x + x) * MINIMAP_SCALE, (center_y + y) * MINIMAP_SCALE, &cub3d->img, red);
            y++;
        }
        x++;
    }
    /*draw_line(&cub3d->img, center_x, center_y, 
              center_x + (int)(cub3d->pdx * MINIMAP_SCALE), 
              center_y + (int)(cub3d->pdy * MINIMAP_SCALE), red);*/
}

//TODO: des le debut ou juste pour minimap ?
void    draw_background(t_raycaster *cub3d) 
{
    int	x;
    int	y;

    y = 0;
    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            my_pixel_put(x, y, &cub3d->img, cub3d->background_color);
            x++;
        }
        y++;
    }
}
/*
void    draw_map(t_raycaster *cub3d)
{
    int x = 0; //max = 8
    int y = 0;
    int xo; // Position du carré en pixels
    int yo;
    int color;
    int scale = PX_SIZE * MINIMAP_SCALE;
 
    while (y < cub3d->lines)
    {
        x = 0;
        while (x < cub3d->col)
        {
            // Parcourir le tableau
            if(map[y][x] == '1')
                color = 0xFFFFFF;
            else
                color = 0x000000;
            // Parcourir les pixels
            xo = x * scale; 
            yo = y * scale;

            // Dessiner le carré -1 pour la grille
            int i = xo;
            while (i < xo + scale)
            {
                int j = yo;
                while (j < yo + scale)
                {
                    my_pixel_put(i, j, &cub3d->img, color);
                    j++;
                }
                i++;
            }
            x++;
        }
        y++;
    }
}*/

void draw_ceiling_and_floor(t_raycaster *cub3d)
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
                my_pixel_put(x, y, &cub3d->img, cub3d->ceiling_color);
            else
                my_pixel_put(x, y, &cub3d->img, cub3d->floor_color);
            y++;
        }
        x++;
    }
}

float init_horizontal_ray(t_raycaster *cub3d, float first_ray, float *rx, float *ry, float *xo, float *yo)
{
    float aTan = -1 / tan(first_ray);
    
    if (first_ray == 0 || first_ray == PI)
        return (8);  // Skip horizontal checks
    if (first_ray > PI)  // Looking up
    {
        *ry = (floor(cub3d->py / PX_SIZE) * PX_SIZE) - 0.0001;
        *rx = (cub3d->py - *ry) * aTan + cub3d->px;
        *yo = -PX_SIZE;
        *xo = -(*yo) * aTan;
    }
    else  // Looking down
    {
        *ry = (floor(cub3d->py / PX_SIZE) * PX_SIZE) + PX_SIZE;
        *rx = (cub3d->py - *ry) * aTan + cub3d->px;
        *yo = PX_SIZE;
        *xo = -(*yo) * aTan;
    }
    return (0);
}

float init_vertical_ray(t_raycaster *cub3d, float first_ray, float *rx, float *ry, float *xo, float *yo)
{
    float nTan = -tan(first_ray);
    
    if (first_ray == PI/2 || first_ray == 3*PI/2)
        return (8);  // Skip vertical checks
    if (first_ray > PI/2 && first_ray < 3*PI/2)  // Looking left
    {
        *rx = (floor(cub3d->px/PX_SIZE) * PX_SIZE) - 0.0001;
        *ry = (cub3d->px - *rx) * nTan + cub3d->py;
        *xo = -PX_SIZE;
        *yo = -(*xo) * nTan;
    }
    else  // Looking right
    {
        *rx = (floor(cub3d->px/PX_SIZE) * PX_SIZE) + PX_SIZE;
        *ry = (cub3d->px - *rx) * nTan + cub3d->py;
        *xo = PX_SIZE;
        *yo = -(*xo) * nTan;
    }
    return (0);
}

int get_map_position(float rx, float ry)
{
    int mx = (int)(rx) / PX_SIZE;
    int my = (int)(ry) / PX_SIZE;
    
    if (mx >= 0 && mx < 8 && my >= 0 && my < 8)
    {
        if (map[my][mx] == '1')
            return (1);
    }
    return (0);
}

float check_wall_hit(float rx, float ry, float px, float py)
{
    int mx = (int)(rx) / PX_SIZE;
    int my = (int)(ry) / PX_SIZE;
    if (mx >= 0 && mx < 8 && my >= 0 && my < 8 && map[my][mx] == '1')
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

void init_ray_casting(t_raycaster *cub3d, float *first_ray, float *raysfield, int *slice_width)
{
    *raysfield = FOV / NUM_RAYS;
    *first_ray = normalize_angle(cub3d->player_angle - FOV/2);
    *slice_width = WIDTH / NUM_RAYS;
}

float fix_fisheye(float distance, float player_angle, float ray_angle)
{
    float ca = normalize_angle(player_angle - ray_angle);
    return distance * cos(ca);
}

void draw_wall_slice(t_raycaster *cub3d, int r, float disT, int slice_width)
{
    float lineH = (PX_SIZE * HEIGHT) / disT;
    float lineO = (HEIGHT - lineH) / 2;

    if (lineH > HEIGHT)
    {
        lineH = HEIGHT;
        lineO = 0;
    }

    int i = 0;
    while (i < slice_width)
    {
        int j = 0;
        while (j < lineH)
        {
            my_pixel_put(r * slice_width + i, j + lineO, &cub3d->img, 
                        cub3d->wall_color);
            j++;
        }
        i++;
    }
}

float check_horizontal_lines(t_raycaster *cub3d, float first_ray, float *hx, float *hy)
{
    float rx, ry, xo, yo;
    int dof = 0;
    float wall_distance = 1000000;

    dof = init_horizontal_ray(cub3d, first_ray, &rx, &ry, &xo, &yo);
    while (dof < 8)
    {
        if (get_map_position(rx, ry))
        {
            wall_distance = check_wall_hit(rx, ry, cub3d->px, cub3d->py);
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

float check_vertical_lines(t_raycaster *cub3d, float first_ray, float *vx, float *vy)
{
    float rx, ry, xo, yo;
    int dof = 0;
    float disV = 1000000;

    dof = init_vertical_ray(cub3d, first_ray, &rx, &ry, &xo, &yo);
    while (dof < 8)
    {
        if (get_map_position(rx, ry))
        {
            disV = check_wall_hit(rx, ry, cub3d->px, cub3d->py);
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

void drawRays2D(t_raycaster *cub3d)
{
    float raysfield, first_ray;  
    int slice_width;
    float hx, hy, vx, vy;
    float wall_distance, disV;
    int r = 0;

    draw_ceiling_and_floor(cub3d);
    init_ray_casting(cub3d, &first_ray, &raysfield, &slice_width);

    while (r < NUM_RAYS)
    {
        wall_distance = check_horizontal_lines(cub3d, first_ray, &hx, &hy);
        disV = check_vertical_lines(cub3d, first_ray, &vx, &vy);

        if (disV < wall_distance)
        {
            cub3d->wall_color = 0xE60000;  // Vertical walls
            wall_distance = disV;
        }
        else
            cub3d->wall_color = 0xB30000;  // Horizontal walls

        wall_distance = fix_fisheye(wall_distance, cub3d->player_angle, first_ray);
        draw_wall_slice(cub3d, r, wall_distance, slice_width);

        first_ray = normalize_angle(first_ray + raysfield);
        r++;
    }
}

void	cub3d_draw(t_raycaster *cub3d)
{
    draw_background(cub3d);
    drawRays2D(cub3d);
    draw_map(cub3d);
    draw_player(cub3d, 2);
    mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
        cub3d->img.img_ptr, 0, 0);
}

int moves(int key, t_raycaster *cub3d)
{
    if (key == XK_Escape)
        end_cub3d(cub3d);
    else if (key == XK_Right) // Turn right 
    {
        cub3d->player_angle += 0.1;
        if (cub3d->player_angle > 2*PI)
            cub3d->player_angle -= 2*PI;
        cub3d->pdx = cos(cub3d->player_angle) * 5;
        cub3d->pdy = sin(cub3d->player_angle) * 5;
    }
    else if (key == XK_Left) // Turn left
    {
        cub3d->player_angle -= 0.1;
        if (cub3d->player_angle < 0)
            cub3d->player_angle += 2*PI;
        cub3d->pdx = cos(cub3d->player_angle) * 5;
        cub3d->pdy = sin(cub3d->player_angle) * 5;
    }  
    else if (key == XK_w) // Avancer
    {
        double new_px = cub3d->px + cub3d->pdx;
        double new_py = cub3d->py + cub3d->pdy;
        int map_x = (int)(new_px / PX_SIZE);
        int map_y = (int)(new_py / PX_SIZE);
        if(map[map_y][map_x] == '0' || map[map_y][map_x] == 'N')
        {
            cub3d->px += cub3d->pdx;
            cub3d->py += cub3d->pdy;
            printf("x = %f y = %f pa = %f\n\n", cub3d->px, cub3d->py, cub3d->player_angle);
        }
        
    }
    else if (key == XK_s) // Reculer
    {
        double new_px = cub3d->px - cub3d->pdx;
        double new_py = cub3d->py - cub3d->pdy;
        int map_x = (int)(new_px / PX_SIZE);
        int map_y = (int)(new_py / PX_SIZE);
        if(map[map_y][map_x] == '0' || map[map_y][map_x] == 'N')
        {
            cub3d->px -= cub3d->pdx;
            cub3d->py -= cub3d->pdy;
            printf("x = %f y = %f pa = %f\n\n", cub3d->px, cub3d->py, cub3d->player_angle);
        }
        
    }
    else if (key == XK_a) // se decaler a gauche
    {
        double new_px = cub3d->px + cos(cub3d->player_angle - PI/2) * 5;
        double new_py = cub3d->py + sin(cub3d->player_angle - PI/2) * 5;
        int map_x = (int)(new_px / PX_SIZE);
        int map_y = (int)(new_py / PX_SIZE);
        if(map[map_y][map_x] == '0' || map[map_y][map_x] == 'N')
        {
            cub3d->px = new_px;
            cub3d->py = new_py;
            printf("x = %f y = %f pa = %f\n\n", cub3d->px, cub3d->py, cub3d->player_angle);
        }
    }
    else if (key == XK_d) // se decaler a droite
    {
        double new_px = cub3d->px + cos(cub3d->player_angle + PI/2) * 5;
        double new_py = cub3d->py + sin(cub3d->player_angle + PI/2) * 5;
        int map_x = (int)(new_px / PX_SIZE);
        int map_y = (int)(new_py / PX_SIZE);
        if(map[map_y][map_x] == '0' || map[map_y][map_x] == 'N')
        {
            cub3d->px = new_px;
            cub3d->py = new_py;
            printf("x = %f y = %f pa = %f\n\n", cub3d->px, cub3d->py, cub3d->player_angle);
        }
        
    }
    cub3d_draw(cub3d);
    return (0);
}

void	init_events(t_raycaster *cub3d)
{
    mlx_hook(cub3d->win_ptr,KeyPress, KeyPressMask, &moves, cub3d);
    mlx_hook(cub3d->win_ptr, DestroyNotify, 0, end_cub3d, cub3d);
}

int main(int argc, char **argv)
{
    t_raycaster cub3d;

    (void)argc;
    (void)argv;

    init_mlx(&cub3d);
    cub3d_draw(&cub3d);
    init_events(&cub3d);
    mlx_loop(cub3d.mlx_ptr);
}
