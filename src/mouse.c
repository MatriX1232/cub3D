/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:21:25 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/15 19:04:38 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

static void	calculate_rot_dir(t_cub3d *cub3d, int delta_x)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = delta_x * 0.002;
	old_dir_x = cub3d->player->dirx;
	old_plane_x = cub3d->player->planex;
	cub3d->player->dirx = cub3d->player->dirx * cos(rot_speed) - \
		cub3d->player->diry * sin(rot_speed);
	cub3d->player->diry = old_dir_x * sin(rot_speed) + \
		cub3d->player->diry * cos(rot_speed);
	cub3d->player->planex = cub3d->player->planex * cos(rot_speed) - \
		cub3d->player->planey * sin(rot_speed);
	cub3d->player->planey = old_plane_x * sin(rot_speed) + \
		cub3d->player->planey * cos(rot_speed);
}

int	mouse_move(int x, int y, t_cub3d *cub3d)
{
	int	center_x;
	int	center_y;
	int	delta_x;

	center_x = cub3d->win_width / 2;
	center_y = cub3d->win_height / 2;
	delta_x = x - center_x;
	if (delta_x != 0)
		calculate_rot_dir(cub3d, delta_x);
	mlx_mouse_move(cub3d->mlx, cub3d->win, center_x, center_y);
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

int	mouse_release(int button, int x, int y, t_cub3d *cub3d)
{
	(void)x;
	(void)y;
	if (button == 1)
		cub3d->keys.mouse_1 = 0;
	return (0);
}
