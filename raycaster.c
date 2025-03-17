#include <unistd.h>
#include <stdlib.h>
#include <math.h> // Pour les fonctions trigonométriques
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# define WIDTH 1280 // multiple de 64
# define HEIGHT 704 // multiple de 64
# define MINIMAP_WIDTH 200
# define MINIMAP_SCALE 0.2
# define PX_SIZE 64
# define PI 3.14159265358979323846
# define FOV (PI / 3) // Field of view
# define NUM_RAYS 1280

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
    cub3d->px = 96;
    cub3d->py = 96;
    cub3d->col = 8;
    cub3d->lines = 8;
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
void drawRays2D(t_raycaster *cub3d)
{
    int r, mx, my, mp, dof;
    float rx, ry, xo, yo, disT;  
    float raysfield; // en radians
    int slice_width; // en pixels
    float first_ray;
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

    draw_ceiling_and_floor(cub3d);

    // Modifier l'angle de départ et l'incrément
    raysfield = FOV / NUM_RAYS;  // Angle entre chaque rayon //FOV = PI/3
    // first_ray = angle du premier rayon
    // player_angle = orientation du joueur (pa=PI/2)
    first_ray= cub3d->player_angle - (PI/6);  // Start 30 degrees to the left
    if (first_ray < 0)
        first_ray += 2*PI;

    r = 0; // Ray counter
    slice_width = WIDTH / NUM_RAYS;  // Calculate width for each slice

    while (r < NUM_RAYS)  // 60 rays
    {
        // --- Check Horizontal lines ---
        //dof = depth of field (max = number of lines in the map)
        dof = 0; //counter for the depth of field
        float aTan = -1 / tan(first_ray);
        float wall_distance = 1000000, hx = cub3d->px, hy = cub3d->py; //coordonnées du mur

        rx = cub3d->px; //coordonnées du rayon
        ry = cub3d->py;

        // Ajouter une vérification spéciale pour 0 et PI
        if (first_ray == 0 || first_ray == PI)  
        {
            rx = cub3d->px;
            ry = cub3d->py;
            dof = 8;  // Skip horizontal checks
        }
        else if (first_ray > PI) // Ray looking up
        {
            ry = (floor(cub3d->py / 64) * 64) - 0.0001; // trouve la ligne de grille horizontale au-dessus du joueur
            rx = (cub3d->py - ry) * aTan + cub3d->px; // donne la distance verticale entre le joueur et l'intersection
            yo = -64; // prochaine intersection
            xo = -yo * aTan; // prochaine intersection
        }
        else if (first_ray< PI) // Ray looking down
        {
            ry = (floor(cub3d->py / 64) * 64) + 64; // trouve la ligne de grille horizontale en dessous du joueur
            rx = (cub3d->py - ry) * aTan + cub3d->px;
            yo = 64; //prochaine intersection
            xo = -yo * aTan; // prochaine intersection
        }
        else // Ray looking straight left or right 
        //risk of infinite loop because it will never find an horizontal line
        {
            rx = cub3d->px;
            ry = cub3d->py;
            dof = 8; //force exit
        }

        while (dof < 8) 
        { 
            mx = (int)(rx) / 64; //x in the double array
            my = (int)(ry) / 64; //y in the double array
            
            if (mx >= 0 && mx < mapX && my >= 0 && my < mapY)
            {
                mp = my * mapX + mx; //index of the block  (2D -> 1D)
                if (map[mp] == 1)
                {
                    hx = rx;
                    hy = ry;
                    wall_distance = sqrt((hx-cub3d->px)*(hx-cub3d->px) + (hy-cub3d->py)*(hy-cub3d->py)); //Pythagore
                    dof = 8;
                }
                else
                {
                    rx += xo; //rajoute la pas
                    ry += yo;
                    dof += 1;
                }
            }
            else
                dof = 8;
        }

        // --- Check Vertical Lines ---
        dof = 0;
        float nTan = -tan(first_ray);
        float disV = 1000000, vx = cub3d->px, vy = cub3d->py;

        // Ajouter une vérification spéciale pour PI/2 et 3*PI/2
        if (first_ray == PI/2 || first_ray == 3*PI/2)
        {
            rx = cub3d->px;
            ry = cub3d->py;
            dof = 8;  // Skip vertical checks
        }
        else if (first_ray> PI/2 && first_ray< 3*PI/2) // Ray looking left
        {
            rx = (floor(cub3d->px/64) * 64) - 0.0001;
            ry = (cub3d->px - rx) * nTan + cub3d->py;
            xo = -64;
            yo = -xo * nTan;
        }
        else if (first_ray< PI/2 || first_ray> 3*PI/2) // Ray looking right
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
        if (disV < wall_distance)
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
            disT = wall_distance;
            cub3d->wall_color = 0xB30000;  // Darker red for horizontal walls
            //draw_line(&cub3d->img, cub3d->px, cub3d->py, rx, ry, 0xFF0000);
        }
    
        // Draw 3D walls
        // Modifier la correction fisheye
        float ca = cub3d->player_angle - first_ray;
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

        first_ray+= raysfield;  // Utiliser l'angle calculé au lieu de PI/180
        if (first_ray> 2*PI)
            first_ray-= 2*PI;
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
        double new_px = cub3d->px + cos(cub3d->player_angle - PI/2) * 5;
        double new_py = cub3d->py + sin(cub3d->player_angle - PI/2) * 5;
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
        double new_px = cub3d->px + cos(cub3d->player_angle + PI/2) * 5;
        double new_py = cub3d->py + sin(cub3d->player_angle + PI/2) * 5;
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
