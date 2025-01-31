/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:39:54 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/04 14:40:13 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	move_forward(t_cub3d *cub3d)
{
	double	move_step_x;
	double	move_step_y;
	double	d_vars[3];
	int		i_vars[2];

	d_vars[0] = cub3d->player->move_speed;
	if (cub3d->player->is_sprint)
		d_vars[0] *= 1.5;
	move_step_x = cub3d->player->dirx * d_vars[0];
	move_step_y = cub3d->player->diry * d_vars[0];
	d_vars[1] = cub3d->player->posx + move_step_x;
	i_vars[0] = (int)d_vars[1];
	i_vars[1] = (int)cub3d->player->posy;
	if (i_vars[0] >= 0 && i_vars[0] < cub3d->map->width
		&& i_vars[1] >= 0 && i_vars[1] < cub3d->map->height
		&& cub3d->map->grid[i_vars[1]][i_vars[0]] == '0')
		cub3d->player->posx = d_vars[1];
	d_vars[2] = cub3d->player->posy + move_step_y;
	i_vars[0] = (int)cub3d->player->posx;
	i_vars[1] = (int)d_vars[2];
	if (i_vars[1] >= 0 && i_vars[1] < cub3d->map->height
		&& i_vars[0] >= 0 && i_vars[0] < cub3d->map->width
		&& cub3d->map->grid[i_vars[1]][i_vars[0]] == '0')
		cub3d->player->posy = d_vars[2];
}

void	move_backward(t_cub3d *cub3d)
{
	double	move_step_x;
	double	move_step_y;
	double	d_vars[3];
	int		i_vars[2];

	d_vars[0] = cub3d->player->move_speed;
	if (cub3d->player->is_sprint)
		d_vars[0] *= 1.5;
	move_step_x = -cub3d->player->dirx * d_vars[0];
	move_step_y = -cub3d->player->diry * d_vars[0];
	d_vars[1] = cub3d->player->posx + move_step_x;
	i_vars[0] = (int)d_vars[1];
	i_vars[1] = (int)cub3d->player->posy;
	if (i_vars[0] >= 0 && i_vars[0] < cub3d->map->width
		&& i_vars[1] >= 0 && i_vars[1] < cub3d->map->height
		&& cub3d->map->grid[i_vars[1]][i_vars[0]] == '0')
		cub3d->player->posx = d_vars[1];
	d_vars[2] = cub3d->player->posy + move_step_y;
	i_vars[0] = (int)cub3d->player->posx;
	i_vars[1] = (int)d_vars[2];
	if (i_vars[1] >= 0 && i_vars[1] < cub3d->map->height
		&& i_vars[0] >= 0 && i_vars[0] < cub3d->map->width
		&& cub3d->map->grid[i_vars[1]][i_vars[0]] == '0')
		cub3d->player->posy = d_vars[2];
}

void	move_left(t_cub3d *cub3d)
{
	double	move_step_x;
	double	move_step_y;
	double	d_vars[3];
	int		i_vars[2];

	d_vars[0] = cub3d->player->move_speed;
	if (cub3d->player->is_sprint)
		d_vars[0] *= 1.5;
	move_step_x = -cub3d->player->planex * d_vars[0];
	move_step_y = -cub3d->player->planey * d_vars[0];
	d_vars[1] = cub3d->player->posx + move_step_x;
	i_vars[0] = (int)d_vars[1];
	i_vars[1] = (int)cub3d->player->posy;
	if (i_vars[0] >= 0 && i_vars[0] < cub3d->map->width
		&& i_vars[1] >= 0 && i_vars[1] < cub3d->map->height
		&& cub3d->map->grid[i_vars[1]][i_vars[0]] == '0')
		cub3d->player->posx = d_vars[1];
	d_vars[2] = cub3d->player->posy + move_step_y;
	i_vars[0] = (int)cub3d->player->posx;
	i_vars[1] = (int)d_vars[2];
	if (i_vars[1] >= 0 && i_vars[1] < cub3d->map->height
		&& i_vars[0] >= 0 && i_vars[0] < cub3d->map->width
		&& cub3d->map->grid[i_vars[1]][i_vars[0]] == '0')
		cub3d->player->posy = d_vars[2];
}

void	move_right(t_cub3d *cub3d)
{
	double	move_step_x;
	double	move_step_y;
	double	d_vars[3];
	int		i_vars[2];

	d_vars[0] = cub3d->player->move_speed;
	if (cub3d->player->is_sprint)
		d_vars[0] *= 1.5;
	move_step_x = cub3d->player->planex * d_vars[0];
	move_step_y = cub3d->player->planey * d_vars[0];
	d_vars[1] = cub3d->player->posx + move_step_x;
	i_vars[0] = (int)d_vars[1];
	i_vars[1] = (int)cub3d->player->posy;
	if (i_vars[0] >= 0 && i_vars[0] < cub3d->map->width
		&& i_vars[1] >= 0 && i_vars[1] < cub3d->map->height
		&& cub3d->map->grid[i_vars[1]][i_vars[0]] == '0')
		cub3d->player->posx = d_vars[1];
	d_vars[2] = cub3d->player->posy + move_step_y;
	i_vars[0] = (int)cub3d->player->posx;
	i_vars[1] = (int)d_vars[2];
	if (i_vars[1] >= 0 && i_vars[1] < cub3d->map->height
		&& i_vars[0] >= 0 && i_vars[0] < cub3d->map->width
		&& cub3d->map->grid[i_vars[1]][i_vars[0]] == '0')
		cub3d->player->posy = d_vars[2];
}
