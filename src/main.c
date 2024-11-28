/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:32:15 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/29 00:08:09 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"


// Define movement speed

int ft_exit(t_cub3d *cub3d)
{
	ft_free_all(cub3d);
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free(cub3d->mlx);
	exit(0);
	return (0);
}

int mouse_move(int x, int y, t_cub3d *cub3d)
{
	int center_x = cub3d->win_width / 2;
	// int center_y = cub3d->win_height / 2;
	double rotSpeed;
	int delta_x = x - center_x;
	if (delta_x != 0)
	{
		rotSpeed = delta_x * 0.002;
		double oldDirX = cub3d->player->dirx;
		double oldPlaneX = cub3d->player->planex;
		cub3d->player->dirx = cub3d->player->dirx * cos(-rotSpeed) - cub3d->player->diry * sin(-rotSpeed);
		cub3d->player->diry = oldDirX * sin(-rotSpeed) + cub3d->player->diry * cos(-rotSpeed);
		cub3d->player->planex = cub3d->player->planex * cos(-rotSpeed) - cub3d->player->planey * sin(-rotSpeed);
		cub3d->player->planey = oldPlaneX * sin(-rotSpeed) + cub3d->player->planey * cos(-rotSpeed);
	}
	(void)y;
	return (0);
}

int main_loop(t_cub3d *cub3d)
{
	handle_input(cub3d);
	raycaster(cub3d);
	return (0);
}

void initialize_keys(t_cub3d *cub3d)
{
	cub3d->keys.w = 0;
	cub3d->keys.a = 0;
	cub3d->keys.s = 0;
	cub3d->keys.d = 0;
	cub3d->keys.left = 0;
	cub3d->keys.right = 0;
}

int	main(int argc, char **argv)
{
	(void)argc;

	t_cub3d cub3d;

	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, 800, 600, "CUB3D");
	if (!mlx || !win)
		return (ft_log("Failed to initialize MLX or create window", NULL, 3), 1);
	ft_log("MLX and WIN initialized", NULL, 1);

	cub3d.win_width = 800;
	cub3d.win_height = 600;

	cub3d.mlx = mlx;
	cub3d.win = win;

	cub3d.sprites = ft_load_sprites(&cub3d);
	if (!cub3d.sprites)
		return (ft_log("Sprites failed to load", NULL, 3), 1);
	// Initialize buffer
	cub3d.buffer = (t_sprite *) malloc(sizeof(t_sprite));
	if (!cub3d.buffer)
		return (ft_log("Failed to allocate memory for sprite buffer", NULL, 3), 1);
	cub3d.buffer->img = mlx_new_image(mlx, cub3d.win_width, cub3d.win_height);
	if (!cub3d.buffer->img)
		return (ft_log("Failed to create new image", NULL, 3), 1);
	cub3d.buffer->addr = mlx_get_data_addr(cub3d.buffer->img, &cub3d.buffer->bits_per_pixel, &cub3d.buffer->line_length, &cub3d.buffer->endian);
	if (!cub3d.buffer->addr)
		return (ft_log("Failed to get data address", NULL, 3), 1);
	cub3d.buffer->width = cub3d.win_width;
	cub3d.buffer->height = cub3d.win_height;


	cub3d.map = ft_load_map(&cub3d, argv[1]);
	if (!cub3d.map)
		return (ft_log("Map failed to load", NULL, 3), 1);
	cub3d.player = cub3d.map->player;
	initialize_keys(&cub3d);
	cub3d.frame = 0;
	cub3d.prev_time = get_timestamp();
	cub3d.delta_time = 0;

	cub3d.anims = ft_laod_anims(&cub3d);
	if (!cub3d.anims)
		return (ft_log("Anims failed to load", NULL, 3), 1);

	// ft_anim(&cub3d);

	mlx_loop_hook(mlx, main_loop, &cub3d);
	mlx_hook(cub3d.win, ON_DESTROY, 0, ft_exit, &cub3d);
	mlx_hook(cub3d.win, KeyPress, KeyPressMask, ft_key_press, &cub3d);
	mlx_hook(cub3d.win, KeyRelease, KeyReleaseMask, ft_key_release, &cub3d);
	mlx_hook(cub3d.win, MotionNotify, PointerMotionMask, mouse_move, &cub3d);
	mlx_loop(mlx);
	return (0);
}
