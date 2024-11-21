/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:32:15 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/21 23:41:42 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

int ft_exit(t_cub3d *cub3d)
{
	ft_free_sprites(cub3d);
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free(cub3d->mlx);
	exit(0);
	return (0);
}

int	ft_key_hook(int keycode, t_cub3d *cub3d)
{
	if (keycode == KEY_ESC)
		ft_exit(cub3d);
	return (0);
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
	cub3d.sprites = ft_load_sprites(mlx);
	if (!cub3d.sprites)
		return (ft_log("Sprites failed to load", NULL, 3), 1);
	cub3d.map = ft_load_map(argv[1]);
	if (!cub3d.map)
		return (ft_log("Map failed to load", NULL, 3), 1);

	mlx_hook(cub3d.win, ON_DESTROY, 0, ft_exit, &cub3d);
	mlx_key_hook(cub3d.win, ft_key_hook, &cub3d);

	cub3d.buffer = (t_sprite *) malloc(sizeof(t_sprite));
	if (!cub3d.buffer)
		return (ft_log("Failed to allocate memory for sprite buffer", NULL, 3), 1);
	cub3d.buffer->img = mlx_new_image(mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub3d.buffer->img)
		return (ft_log("Failed to create new image", NULL, 3), 1);
	cub3d.buffer->addr = mlx_get_data_addr(cub3d.buffer->img, &cub3d.buffer->bits_per_pixel, &cub3d.buffer->line_length, &cub3d.buffer->endian);
	if (!cub3d.buffer->addr)
		return (ft_log("Failed to get data address", NULL, 3), 1);
	int	i = 0;
	while (cub3d.sprites[i])
	{
		put_img_to_img(cub3d.buffer, cub3d.sprites[i], i * 70, 0);
		i++;
	}
	ft_draw_minimap(&cub3d, 5, 3);
	mlx_put_image_to_window(mlx, win, cub3d.buffer->img, 0, 0);

	mlx_loop(mlx);

	return (0);
}
