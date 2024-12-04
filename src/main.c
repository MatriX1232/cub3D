/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:32:15 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/04 12:17:30 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

int ft_exit(t_cub3d *cub3d)
{
	ft_free_all(cub3d);
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

int	mouse_press(int button, int x, int y, t_cub3d *cub3d)
{
	(void)x;
	(void)y;
	if (button == 1)
		cub3d->keys.mouse_1 = 1;
	return (0);
}

int mouse_release(int button, int x, int y, t_cub3d *cub3d)
{
	(void)x;
	(void)y;
	if (button == 1)
		cub3d->keys.mouse_1 = 0;
	return (0);
}

int main_loop(t_cub3d *cub3d)
{
	double current_time = get_timestamp();
	double frame_time = (current_time - cub3d->prev_time) / 1000.0;
	if (FRAME_RATE > 0)
	{
		double min_frame_time = 1.0 / FRAME_RATE;
		if (frame_time < min_frame_time)
		{
			usleep((useconds_t)((min_frame_time - frame_time) * 1000000));
			current_time = get_timestamp();
			frame_time = (current_time - cub3d->prev_time) / 1000.0;
		}
	}
	cub3d->delta_time = frame_time;
	cub3d->prev_time = current_time;
	handle_input(cub3d);
	raycaster(cub3d);
	if (cub3d->gun_shooting)
		update_animation(cub3d, cub3d->anims[cub3d->player->current_weapon->index - 1]);
	draw_2_buffer(cub3d->buffer, cub3d->anims[cub3d->player->current_weapon->index - 1]->sprites[cub3d->anims[cub3d->player->current_weapon->index - 1]->frame], (int)((WIN_WIDTH / 2) - 150), WIN_HEIGHT - 300);
	ft_render_hud(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->buffer->img, 0, 0);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->buffer_HUD->img, 0, WIN_HEIGHT - 1);
	int fps = (int)(1.0 / frame_time);
	char *fps_str = ft_itoa(fps);
	mlx_string_put(cub3d->mlx, cub3d->win, 10, 20, 0xFFFFFF, "FPS:");
	mlx_string_put(cub3d->mlx, cub3d->win, 50, 20, 0xFFFFFF, fps_str);
	free(fps_str);
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
	cub3d->keys.shift = 0;
	cub3d->keys.mouse_1 = 0;
	cub3d->keys.up = 0;
	cub3d->keys.down = 0;
	cub3d->player->move_speed = MOVE_SPEED;
}

t_sprite	*ft_create_blank(t_cub3d *cub3d, int width, int height)
{
	t_sprite	*image;

	image = (t_sprite *) malloc(1 * sizeof(t_sprite));
	if (!image)
		return (ft_log("Failed to allocate memory for blank image", NULL, 3), NULL);
	image->img = mlx_new_image(cub3d->mlx, width, height);
	if (!image->img)
		return (ft_log("Failed to create new image", NULL, 3), NULL);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel, &image->line_length, &image->endian);
	if (!image->addr)
		return (ft_log("Failed to get data address", NULL, 3), NULL);
	image->width = width;
	image->height = height;
	return (image);
}

int	main(int argc, char **argv)
{
	(void)argc;

	t_cub3d cub3d;

	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, ALL_WIDTH, ALL_HEIGHT, "CUB3D");
	if (!mlx || !win)
		return (ft_log("Failed to initialize MLX or create window", NULL, 3), 1);
	ft_log("MLX and WIN initialized", NULL, 1);

	cub3d.win_width = WIN_WIDTH;
	cub3d.win_height = WIN_HEIGHT;

	cub3d.mlx = mlx;
	cub3d.win = win;

	cub3d.sprites = ft_load_sprites(&cub3d);
	cub3d.HUD = xpm_load_image(mlx, "textures/hud.xpm", 0);
	if (!cub3d.sprites || !cub3d.HUD)
		return (ft_log("Sprites failed to load", NULL, 3), 1);

	// Initialize buffer
	cub3d.buffer = ft_create_blank(&cub3d, cub3d.win_width, cub3d.win_height);
	cub3d.buffer_HUD = ft_create_blank(&cub3d, ALL_WIDTH, ALL_HEIGHT - WIN_HEIGHT);
	if (!cub3d.buffer || !cub3d.buffer_HUD)
		return (ft_log("Failed to create buffer", NULL, 3), 1);

	cub3d.characters = load_font(&cub3d, "textures/font/", 30);
	if (!cub3d.characters)
		return (ft_log("Failed to load font characters", NULL, 3), 1);

	// splash_screen(&cub3d);

	cub3d.map = ft_load_map(&cub3d, argv[1]);
	if (!cub3d.map)
		return (ft_log("Map failed to load", NULL, 3), 1);

	cub3d.anims = ft_load_anims(&cub3d);
	if (!cub3d.anims)
		return (ft_log("Anims failed to load", NULL, 3), 1);
	if (!cub3d.player)
		return (ft_log("Player failed to load", NULL, 3), 1);

	cub3d.player->current_weapon = &cub3d.weapons[1];
	cub3d.player->pitch = 100;
	initialize_keys(&cub3d);
	cub3d.frame = 0;
	cub3d.prev_time = get_timestamp();
	cub3d.delta_time = 0;

	cub3d.gun_shooting = 0;
	cub3d.prev_shoot = 0;

	// Register mouse press callback
	// mlx_mouse_hook(win, mouse_press, &cub3d);

	mlx_loop_hook(mlx, main_loop, &cub3d);
	mlx_hook(cub3d.win, ON_DESTROY, 0, ft_exit, &cub3d);
	mlx_hook(cub3d.win, ButtonPress, ButtonPressMask, mouse_press, &cub3d);
	mlx_hook(cub3d.win, ButtonRelease, ButtonReleaseMask, mouse_release, &cub3d);
	mlx_hook(cub3d.win, KeyPress, KeyPressMask, ft_key_press, &cub3d);
	mlx_hook(cub3d.win, KeyRelease, KeyReleaseMask, ft_key_release, &cub3d);
	mlx_hook(cub3d.win, MotionNotify, PointerMotionMask, mouse_move, &cub3d);
	mlx_loop(mlx);
	return (0);
}
