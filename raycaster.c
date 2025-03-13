#include <unistd.h>
#include <stdlib.h>
#include <math.h> // Pour les fonctions trigonométriques
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# define WIDTH 1280
# define HEIGHT 720
# define MINIMAP_WIDTH 200
# define MINIMAP_SCALE 0.2
# define PX_SIZE 64
# define PI 3.14159265358979323846
# define NUM_RAYS 60

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
    int     wall_color;
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
    int center_x = cub3d->px * MINIMAP_SCALE;
    int center_y = cub3d->py * MINIMAP_SCALE;
    int yellow = 0xFFFF00;
    int x = -(size * MINIMAP_SCALE) / 2;
    int y;

    while (x <= (size * MINIMAP_SCALE) / 2)
    {
        y = -(size * MINIMAP_SCALE) / 2;
        while (y <= (size * MINIMAP_SCALE) / 2)
        {
            my_pixel_put(center_x + x, center_y + y, &cub3d->img, yellow);
            y++;
        }
        x++;
    }
    draw_line(&cub3d->img, center_x, center_y, center_x + (int)(cub3d->pdx * 5 * MINIMAP_SCALE), center_y + (int)(cub3d->pdy * 5 * MINIMAP_SCALE), yellow);
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
    int scale = PX_SIZE * MINIMAP_SCALE;
 
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
            xo = x * scale; 
            yo = y * scale;

            // Dessiner le carré -1 pour la grille
            int i = xo + 1;
            while (i < xo + scale - 1)
            {
                int j = yo + 1;
                while (j < yo + scale - 1)
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
    float rx, ry, ra, xo, yo, disT;  
    int mapX = 8;
    int mapY = 8;
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

    // Draw floor and ceiling in 3D view
    int x = 0;
    while (x < WIDTH)
    {
        int y = 0;
        while (y < HEIGHT)
        {
            if (y > HEIGHT/2)  // Floor
                my_pixel_put(x, y, &cub3d->img, 0x4A4A4A);
            y++;
        }
        x++;
    }

    // Modifier l'angle de départ et l'incrément
    float angleStep = (PI/3) / NUM_RAYS;  // Angle entre chaque rayon
    ra = cub3d->pa - (PI/6);  // Start 30 degrees to the left

    r = 0;
    float slice_width = (float)WIDTH / NUM_RAYS;  // Calculate width for each slice

    while (r < NUM_RAYS)  // 60 rays for 60 degree FOV
    {
        // --- Check Horizontal lines ---
        dof = 0;
        float aTan = -1 / tan(ra);
        float disH = 1000000, hx = cub3d->px, hy = cub3d->py;

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
        else // Ray looking straight left or right
        {
            rx = cub3d->px;
            ry = cub3d->py;
            dof = 8;
        }

        while (dof < 8) 
        { 
            mx = (int)(rx) / 64;
            my = (int)(ry) / 64;
            
            if (mx >= 0 && mx < mapX && my >= 0 && my < mapY)
            {
                mp = my * mapX + mx;
                if (mp >= 0 && mp < mapX * mapY && map[mp] == 1)
                {
                    hx = rx;
                    hy = ry;
                    disH = sqrt((hx-cub3d->px)*(hx-cub3d->px) + (hy-cub3d->py)*(hy-cub3d->py)); //Pythagore
                    dof = 8;
                }
                else
                {
                    rx += xo;
                    ry += yo;
                    dof += 1;
                }
            }
            else
                dof = 8;
        }

        // --- Check Vertical Lines ---
        dof = 0;
        float nTan = -tan(ra);
        float disV = 1000000, vx = cub3d->px, vy = cub3d->py;

        if (ra > PI/2 && ra < 3*PI/2) // Ray looking left
        {
            rx = (floor(cub3d->px/64) * 64) - 0.0001;
            ry = (cub3d->px - rx) * nTan + cub3d->py;
            xo = -64;
            yo = -xo * nTan;
        }
        else if (ra < PI/2 || ra > 3*PI/2) // Ray looking right
        {
            rx = (floor(cub3d->px/64) * 64) + 64;
            ry = (cub3d->px - rx) * nTan + cub3d->py;
            xo = 64;
            yo = -xo * nTan;
        }
        else // Looking straight up or down
        {
            rx = cub3d->px;
            ry = cub3d->py;
            dof = 8;
        }

        while (dof < 8)
        {
            mx = (int)(rx) / 64;
            my = (int)(ry) / 64;
            
            if (mx >= 0 && mx < mapX && my >= 0 && my < mapY)
            {
                mp = my * mapX + mx;
                if (mp >= 0 && mp < mapX * mapY && map[mp] == 1)
                {
                    vx = rx;
                    vy = ry;
                    disV = sqrt((vx-cub3d->px)*(vx-cub3d->px) + (vy-cub3d->py)*(vy-cub3d->py));
                    dof = 8;
                }
                else
                {
                    rx += xo;
                    ry += yo;
                    dof += 1;
                }
            }
            else
                dof = 8;
        }

        // Draw the shortest ray
        if (disV < disH)
        {
            rx = vx;
            ry = vy;
            disT = disV;
            cub3d->wall_color = 0xE60000;  // Lighter red for vertical walls
            //draw_line(&cub3d->img, cub3d->px, cub3d->py, rx, ry, 0x0000FF);
        }
        else
        {
            rx = hx;
            ry = hy;
            disT = disH;
            cub3d->wall_color = 0xB30000;  // Darker red for horizontal walls
            //draw_line(&cub3d->img, cub3d->px, cub3d->py, rx, ry, 0xFF0000);
        }
    
        // Draw 3D walls
        // Modifier la correction fisheye
        float ca = cub3d->pa - ra;
        if (ca < 0) ca += 2*PI;
        if (ca > 2*PI) ca -= 2*PI;
        disT = disT * cos(ca);  // Fix fisheye
        
        // Ajuster la hauteur des murs
        float lineH = (PX_SIZE * HEIGHT) / disT;
        float lineO = (HEIGHT - lineH) / 2;  // Centre vertical

        if (lineH > HEIGHT)
        {
            lineH = HEIGHT;
            lineO = 0;
        }

        // Draw wall slice with calculated width
        int i = 0;
        while (i < slice_width)  // Use calculated slice width instead of fixed 8
        {
            int j = 0;
            while (j < lineH)
            {
                my_pixel_put(r * slice_width + i, j + lineO, &cub3d->img, cub3d->wall_color);
                j++;
            }
            i++;
        }

        ra += angleStep;  // Utiliser l'angle calculé au lieu de PI/180
        if (ra > 2*PI)
            ra -= 2*PI;
        r++;
    }
}

void	cub3d_draw(t_raycaster *cub3d)
{
    draw_background(cub3d);
    drawRays2D(cub3d);
    draw_map(cub3d);
    draw_player(cub3d, 8);
    mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
        cub3d->img.img_ptr, 0, 0);
}

//if(map[y * cub3d->col + x] == 1)

int moves(int key, t_raycaster *cub3d)
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
    if (key == XK_Escape)
        end_cub3d(cub3d);
    else if (key == XK_Right) // Turn right 
    {
        cub3d->pa += 0.1;
        if (cub3d->pa > 2*PI)
            cub3d->pa -= 2*PI;
        cub3d->pdx = cos(cub3d->pa) * 5;
        cub3d->pdy = sin(cub3d->pa) * 5;
    }
    else if (key == XK_Left) // Turn left
    {
        cub3d->pa -= 0.1;
        if (cub3d->pa < 0)
            cub3d->pa += 2*PI;
        cub3d->pdx = cos(cub3d->pa) * 5;
        cub3d->pdy = sin(cub3d->pa) * 5;
    }  
    else if (key == XK_w) // Avancer
    {
        double new_px = cub3d->px + cub3d->pdx;
        double new_py = cub3d->py + cub3d->pdy;
        int map_x = (int)(new_px / PX_SIZE);
        int map_y = (int)(new_py / PX_SIZE);
        if(map[map_y * cub3d->col + map_x] == 0)
        {
            cub3d->px += cub3d->pdx;
            cub3d->py += cub3d->pdy;
        }
    }
    else if (key == XK_s) // Reculer
    {
        double new_px = cub3d->px - cub3d->pdx;
        double new_py = cub3d->py - cub3d->pdy;
        int map_x = (int)(new_px / PX_SIZE);
        int map_y = (int)(new_py / PX_SIZE);
        if(map[map_y * cub3d->col + map_x] == 0)
        {
            cub3d->px -= cub3d->pdx;
            cub3d->py -= cub3d->pdy;
        }
    }
    else if (key == XK_a) // se decaler a gauche
    {
        double new_px = cub3d->px + cos(cub3d->pa - PI/2) * 5;
        double new_py = cub3d->py + sin(cub3d->pa - PI/2) * 5;
        int map_x = (int)(new_px / PX_SIZE);
        int map_y = (int)(new_py / PX_SIZE);
        if(map[map_y * cub3d->col + map_x] == 0)
        {
            cub3d->px = new_px;
            cub3d->py = new_py;
        }
    }
    else if (key == XK_d) // se decaler a droite
    {
        double new_px = cub3d->px + cos(cub3d->pa + PI/2) * 5;
        double new_py = cub3d->py + sin(cub3d->pa + PI/2) * 5;
        int map_x = (int)(new_px / PX_SIZE);
        int map_y = (int)(new_py / PX_SIZE);
        if(map[map_y * cub3d->col + map_x] == 0)
        {
            cub3d->px = new_px;
            cub3d->py = new_py;
        }
    }
    cub3d_draw(cub3d);
    return (0);
}

void	init_events(t_raycaster *cub3d)
{
    //mlx_key_hook(cub3d->win_ptr, key_hook, cub3d);
    //mlx_mouse_hook(cub3d->win_ptr, mouse_hook, cub3d);
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
