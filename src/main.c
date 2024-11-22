/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:32:15 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/21 14:17:50 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

int ft_exit(t_cub3d *cub3d)
{
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
	(void)argv;

	t_cub3d cub3d;
	cub3d.h = 600;
	cub3d.w = 800;


	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, cub3d.w, cub3d.h, "CUB3D");
	
	cub3d.mlx = mlx;
	cub3d.win = win;
	cub3d.sprites = ft_load_sprites(mlx);

	mlx_hook(cub3d.win, ON_DESTROY, 0, ft_exit, &cub3d);
	mlx_key_hook(cub3d.win, ft_key_hook, &cub3d);
	// mlx_put_image_to_window(mlx, win, cub3d.sprites[0]->img, 0, 0);
	raycaster(&cub3d);
	mlx_loop(mlx);

	return (0);
}
