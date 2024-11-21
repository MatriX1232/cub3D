/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:32:15 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/21 13:49:27 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/mlx.h"
#include "../include/mlx_int.h"
#include "../include/cub3d.h"
#include <stdio.h>

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

	void	*mlx = mlx_init();
	void	*win = mlx_new_window(mlx, 800, 600, "CUB3D");

	cub3d.mlx = mlx;
	cub3d.win = win;

	mlx_hook(cub3d.win, 17, 0, ft_exit, &cub3d);
	mlx_key_hook(cub3d.win, ft_key_hook, &cub3d);
	mlx_loop(mlx);

	return (0);
}
