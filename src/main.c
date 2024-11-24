/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:32:15 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/22 17:57:51 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"
#include <stdbool.h>


#include <X11/keysym.h>

#define KEY_W 119 // ASCII for 'w'
#define KEY_A 97  // ASCII for 'a'
#define KEY_S 115 // ASCII for 's'
#define KEY_D 100 // ASCII for 'd'


// Define movement speed
#define MOVE_SPEED 0.05
#define ROT_SPEED 0.03

int ft_exit(t_cub3d *cub3d)
{
	ft_free_sprites(cub3d);
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free(cub3d->mlx);
	exit(0);
	return (0);
}

// Function to handle player movement with collision detection
static void	handle_movement(t_cub3d *cub3d, int keycode)
{
	double new_posx;
	double new_posy;

	if (keycode == KEY_W) // Move forward
	{
		new_posx = cub3d->player->posx + cub3d->player->dirx * MOVE_SPEED;
		new_posy = cub3d->player->posy + cub3d->player->diry * MOVE_SPEED;
		if (cub3d->map->grid[(int)new_posy][(int)new_posx] == '0')
		{
			cub3d->player->posx = new_posx;
			cub3d->player->posy = new_posy;
		}
	}
	else if (keycode == KEY_S) // Move backward
	{
		new_posx = cub3d->player->posx - cub3d->player->dirx * MOVE_SPEED;
		new_posy = cub3d->player->posy - cub3d->player->diry * MOVE_SPEED;
		if (cub3d->map->grid[(int)new_posy][(int)new_posx] == '0')
		{
			cub3d->player->posx = new_posx;
			cub3d->player->posy = new_posy;
		}
	}
	else if (keycode == KEY_A) // Strafe left
	{
		new_posx = cub3d->player->posx - cub3d->player->planex * MOVE_SPEED;
		new_posy = cub3d->player->posy - cub3d->player->planey * MOVE_SPEED;
		if (cub3d->map->grid[(int)new_posy][(int)new_posx] == '0')
		{
			cub3d->player->posx = new_posx;
			cub3d->player->posy = new_posy;
		}
	}
	else if (keycode == KEY_D) // Strafe right
	{
		new_posx = cub3d->player->posx + cub3d->player->planex * MOVE_SPEED;
		new_posy = cub3d->player->posy + cub3d->player->planey * MOVE_SPEED;
		if (cub3d->map->grid[(int)new_posy][(int)new_posx] == '0')
		{
			cub3d->player->posx = new_posx;
			cub3d->player->posy = new_posy;
		}
	}
}

int	ft_key_hook(int keycode, t_cub3d *cub3d)
{
	ft_log("Key pressed", ft_itoa(keycode), 1);
	if (keycode == KEY_ESC)
		ft_exit(cub3d);
	else
		handle_movement(cub3d, keycode);
	raycaster(cub3d);
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;

	t_cub3d cub3d;
	// cub3d.h = 600;
	// cub3d.w = 800;

	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, 800, 600, "CUB3D");
	if (!mlx || !win)
		return (ft_log("Failed to initialize MLX or create window", NULL, 3), 1);
	ft_log("MLX and WIN initialized", NULL, 1);

	cub3d.win_width = 800;
	cub3d.win_height = 600;

	cub3d.mlx = mlx;
	cub3d.win = win;
	cub3d.sprites = ft_load_sprites(mlx);
	if (!cub3d.sprites)
		return (ft_log("Sprites failed to load", NULL, 3), 1);
	cub3d.map = ft_load_map(argv[1]);
	if (!cub3d.map)
		return (ft_log("Map failed to load", NULL, 3), 1);
	cub3d.player = cub3d.map->player;

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

	// Register raycaster as the loop hook
	mlx_loop_hook(mlx, raycaster, &cub3d);

	mlx_hook(cub3d.win, ON_DESTROY, 0, ft_exit, &cub3d);
	mlx_key_hook(cub3d.win, ft_key_hook, &cub3d);

	mlx_loop(mlx);

	return (0);
}
