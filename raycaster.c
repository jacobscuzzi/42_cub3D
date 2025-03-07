#include <unistd.h>
#include <stdlib.h>
#include <math.h> // Pour les fonctions trigonométriques
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# define WIDTH 700
# define HEIGHT 700
# define PX_SIZE 64
# define PI 3.14159265358979323846

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
    double  px; // Position du joueur
    double  py; // Position du joueur
    double  pa; // Orientation du joueur en radians
    double  pdx; // Projection du prochain mouvement
    double  pdy;
    int     col; 
    int     lines;
}   t_raycaster;

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
    cub3d->px = 160;
    cub3d->py = 400;
    cub3d->col = 8;
    cub3d->lines = 8;
    cub3d->pa = 0;
    cub3d->pdx = cos(cub3d->pa) * 5; //cos(0)=1
    cub3d->pdy = sin(cub3d->pa) * 5; //sin(0)=0
}

int	end_cub3d(t_raycaster *cub3d)
{
    mlx_destroy_image(cub3d->mlx_ptr, cub3d->img.img_ptr);
    mlx_destroy_window(cub3d->mlx_ptr, cub3d->win_ptr);
    mlx_destroy_display(cub3d->mlx_ptr);
    free(cub3d->mlx_ptr);
    exit(0);
}

static void	my_pixel_put(int x, int y, t_img *img, int color)
{
    int	offset;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        offset = (y * img->line_len) + (x * (img->bpp / 8));
        *(unsigned int *)(img->pix_ptr + offset) = color;
    }
}

//Bresenham algorithm (not mine)
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

void	draw_player(t_raycaster *cub3d, int size)
{
    int center_x = cub3d->px;
    int center_y = cub3d->py;
    int yellow = 0xFFFF00; // Couleur jaune
    int x = -size / 2;
    int y;

    while (x <= size / 2)
    {
        y = -size / 2;
        while (y <= size / 2)
        {
            my_pixel_put(center_x + x, center_y + y, &cub3d->img, yellow);
            y++;
        }
        x++;
    }
    draw_line(&cub3d->img, center_x, center_y, center_x + (int)(cub3d->pdx * 5), center_y + (int)(cub3d->pdy * 5), yellow);
}

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

void    draw_map(t_raycaster *cub3d)
{
    int map[]=
    {
    1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,	
    };

    int x = 0; //max = 8
    int y = 0;
    int xo; // Position du carré en pixels
    int yo;
    int color;
 
    while (y < cub3d->lines)
    {
        x = 0;
        while (x < cub3d->col)
        {
            // Parcourir le tableau
            if(map[y * cub3d->col + x] == 1)
                color = 0xFFFFFF;
            else
                color = 0x000000;
            // Parcourir les pixels
            xo = x * PX_SIZE; 
            yo = y * PX_SIZE;

            // Dessiner le carré -1 pour la grille
            int i = xo + 1;
            while (i < xo + PX_SIZE - 1)
            {
                int j = yo + 1;
                while (j < yo + PX_SIZE - 1)
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

void drawRays2D(t_raycaster *cub3d)
{
    int r, mx, my, mp, dof;
    float rx, ry, ra, xo, yo;  
    int mapX = 8; // Number of columns in the map
    int mapY = 8; // Number of rows in the map
    int map[64]=
    {
    1,1,1,1,1,1,1,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,1,0,0,0,0,1,
    1,0,0,0,0,0,0,1,
    1,0,0,0,0,1,0,1,
    1,0,0,0,0,0,0,1,
    1,1,1,1,1,1,1,1,	
    };

    ra = cub3d->pa;
    r = 0;

    while (r < 1)
    {
        // --- Check Horizontal lines ---
        dof = 0;
        float aTan = -1 / tan(ra);

        rx = cub3d->px;
        ry = cub3d->py;

        if (ra > PI) // Ray looking up
        {
            ry = (floor(cub3d->py / 64) * 64) - 0.0001;
            rx = (cub3d->py - ry) * aTan + cub3d->px;
            yo = -64;
            xo = -yo * aTan;
        }
        else if (ra < PI) // Ray looking down
        {
            ry = (floor(cub3d->py / 64) * 64) + 64;
            rx = (cub3d->py - ry) * aTan + cub3d->px;
            yo = 64;
            xo = -yo * aTan; 
        }
        else // Ray looking to the left or to the right
        {
            rx = cub3d->px;
            ry = cub3d->py;
            dof = 8;
        }

        while (dof < 8) 
        { 
            mx = (int)(rx) / 64;
            my = (int)(ry) / 64;
            
            // Vérifier que mx et my sont dans les limites
            if (mx >= 0 && mx < mapX && my >= 0 && my < mapY)
            {
                mp = my * mapX + mx;
                if (mp >= 0 && mp < mapX * mapY && map[mp] == 1)
                {
                    dof = 8; // Hit wall
                }
                else
                {
                    rx += xo;
                    ry += yo;
                    dof += 1;
                }
            }
            else
            {
                dof = 8; // Out of bounds
            }
        }

        // Vérifier que les coordonnées sont valides avant de dessiner
        if (rx >= 0 && rx < WIDTH && ry >= 0 && ry < HEIGHT)
        {
            draw_line(&cub3d->img, cub3d->px, cub3d->py, rx, ry, 0xFF0000);
        }
        r++;
    }
}

void	cub3d_draw(t_raycaster *cub3d)
{
    draw_background(cub3d);
    draw_map(cub3d);
    draw_player(cub3d, 8);
    drawRays2D(cub3d);
    mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
        cub3d->img.img_ptr, 0, 0);
}

int	key_hook(int keysym, t_raycaster *cub3d)
{
    if (keysym == XK_Escape)
        end_cub3d(cub3d);
    if (keysym == XK_d) // Tourner à gauche
    {
        cub3d->pa += 0.1;
        if (cub3d->pa > 2*PI)
            cub3d->pa -= 2*PI;
        cub3d->pdx = cos(cub3d->pa) * 5;
        cub3d->pdy = sin(cub3d->pa) * 5;
    }
    else if (keysym == XK_a) // Tourner à droite
    {
        cub3d->pa -= 0.1;
        if (cub3d->pa < 0)
            cub3d->pa += 2*PI;
        cub3d->pdx = cos(cub3d->pa) * 5;
        cub3d->pdy = sin(cub3d->pa) * 5;
    }  
    else if (keysym == XK_w) // Avancer
    {
        cub3d->px += cub3d->pdx;
        cub3d->py += cub3d->pdy;
    }
    else if (keysym == XK_s) // Reculer
    {
        cub3d->px -= cub3d->pdx;
        cub3d->py -= cub3d->pdy;
    }
    cub3d_draw(cub3d);
    return (0);
}

void	init_events(t_raycaster *cub3d)
{
    mlx_key_hook(cub3d->win_ptr, key_hook, cub3d);
    //mlx_mouse_hook(cub3d->win_ptr, mouse_hook, cub3d);
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
