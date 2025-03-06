#include <unistd.h>
#include <stdlib.h>
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# define WIDTH 700
# define HEIGHT 700

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
    int     color;
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
    cub3d->color = 0xFFFFFF;
}

int	end_fractol(t_raycaster *cub3d)
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

void	cub3d_draw(t_raycaster *cub3d)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_pixel_put(x, y, &cub3d->img, cub3d->color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub3d->mlx_ptr, cub3d->win_ptr,
		cub3d->img.img_ptr, 0, 0);
}

int	key_hook(int keysym, t_raycaster *cub3d)
{
	if (keysym == XK_Escape)
		end_fractol(cub3d);
	if (keysym == XK_Right)
    {
        cub3d->color = 0x00ff00;
        cub3d_draw(cub3d);
    }  
    else if (keysym == XK_Left)
    {
        cub3d->color = 0xff0000;
        cub3d_draw(cub3d);
    }
	// 	cub3d->shift_x -= (0.5 * cub3d->zoom);
	// else if (keysym == XK_Up)
	// 	cub3d->shift_y -= (0.5 * cub3d->zoom);
	// else if (keysym == XK_Down)
	// 	cub3d->shift_y += (0.5 * cub3d->zoom);
	cub3d_draw(cub3d);
	return (0);
}

void	init_events(t_raycaster *cub3d)
{
	mlx_key_hook(cub3d->win_ptr, key_hook, cub3d);
	//mlx_mouse_hook(cub3d->win_ptr, mouse_hook, cub3d);
	mlx_hook(cub3d->win_ptr, DestroyNotify, 0, end_fractol, cub3d);
}

int main(int argc, char **argv)
{
    t_raycaster cub3d;

    (void)argc;
    (void)argv;
    init_mlx(&cub3d);
    init_events(&cub3d);
    cub3d_draw(&cub3d);
    mlx_loop(cub3d.mlx_ptr);
}