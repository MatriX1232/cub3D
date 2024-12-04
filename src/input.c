/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:28:34 by idomagal          #+#    #+#             */
/*   Updated: 2024/12/04 14:43:32 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	rotate_left(t_cub3d *cub3d)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	old_dir_x = cub3d->player->dirx;
	old_plane_x = cub3d->player->planex;
	rot_speed = ROT_SPEED;
	cub3d->player->dirx = cub3d->player->dirx * cos(-rot_speed) \
		- cub3d->player->diry * sin(-rot_speed);
	cub3d->player->diry = old_dir_x * sin(-rot_speed) + \
		cub3d->player->diry * cos(-rot_speed);
	cub3d->player->planex = cub3d->player->planex * cos(-rot_speed) \
		- cub3d->player->planey * sin(-rot_speed);
	cub3d->player->planey = old_plane_x * sin(-rot_speed) + \
		cub3d->player->planey * cos(-rot_speed);
}

void	rotate_right(t_cub3d *cub3d)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	old_dir_x = cub3d->player->dirx;
	old_plane_x = cub3d->player->planex;
	rot_speed = ROT_SPEED;
	cub3d->player->dirx = cub3d->player->dirx * cos(rot_speed) - \
		cub3d->player->diry * sin(rot_speed);
	cub3d->player->diry = old_dir_x * sin(rot_speed) + \
		cub3d->player->diry * cos(rot_speed);
	cub3d->player->planex = cub3d->player->planex * \
		cos(rot_speed) - cub3d->player->planey * sin(rot_speed);
	cub3d->player->planey = old_plane_x * sin(rot_speed) + \
		cub3d->player->planey * cos(rot_speed);
}

void	look_up(t_cub3d *cub3d)
{
	double	pitch_speed;

	pitch_speed = 2.0;
	cub3d->player->pitch += pitch_speed;
	if (cub3d->player->pitch > (double)cub3d->win_height / 2)
		cub3d->player->pitch = (double)cub3d->win_height / 2;
}

void	look_down(t_cub3d *cub3d)
{
	double	pitch_speed;

	pitch_speed = 2.0;
	cub3d->player->pitch -= pitch_speed;
	if (cub3d->player->pitch < (double)-cub3d->win_height / 2)
		cub3d->player->pitch = (double)-cub3d->win_height / 2;
}
