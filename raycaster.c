#include <unistd.h>
#include <stdlib.h>
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# define WIDTH 700
# define HEIGHT 700
# define PX_SIZE 64


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
    int     px; //player's position 
    int     py; //player's position
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
			"fractol");
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

void	draw_player(t_raycaster *cub3d, int size)
{
    int center_x = cub3d->px;
    int center_y = cub3d->py;
    int yellow = 0xFFFF00; //Couleur jaune
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
    int xo; //square's position in pixels
    int yo;
    int color;
 
    while (y < cub3d->lines)
    {
        x = 0;
        while (x < cub3d->col)
        {
            //here, we go through the array
            if(map[y * cub3d->col + x] == 1)
                color = 0xFFFFFF;
            else
                color = 0x000000;
            //here, he go through the pixels
            xo = x * PX_SIZE; 
            yo = y * PX_SIZE;

            //draw the square -1 for the grid
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

void	cub3d_draw(t_raycaster *cub3d)
{
    draw_background(cub3d);
    draw_map(cub3d);
    draw_player(cub3d, 8);
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
		cub3d->img.img_ptr, 0, 0);
}

int	key_hook(int keysym, t_raycaster *cub3d)
{
	if (keysym == XK_Escape)
		end_cub3d(cub3d);
	if (keysym == XK_Right)
    {
        cub3d->px += 5;
        cub3d_draw(cub3d);
    }  
    else if (keysym == XK_Left)
    {
        cub3d->px -= 5;
        cub3d_draw(cub3d);
    }
	else if (keysym == XK_Up)
	{
        cub3d->py -= 5;
        cub3d_draw(cub3d);
    }
	else if (keysym == XK_Down)
	{
        cub3d->py += 5;
        cub3d_draw(cub3d);
    }
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

    #define PX_SIZE 64
    init_mlx(&cub3d);
    cub3d_draw(&cub3d);
    init_events(&cub3d);
    mlx_loop(cub3d.mlx_ptr);
}