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

	if (cub3d->player->is_sprint)
		cub3d->player->move_speed *= 1.5;
	move_step_x = cub3d->player->dirx * cub3d->player->move_speed;
	move_step_y = cub3d->player->diry * cub3d->player->move_speed;
	if (cub3d->map->grid[(int)(cub3d->player->posy)]
		[(int)(cub3d->player->posx + move_step_x)] == '0')
		cub3d->player->posx += move_step_x;
	if (cub3d->map->grid[(int)(cub3d->player->posy + move_step_y)]
		[(int)(cub3d->player->posx)] == '0')
		cub3d->player->posy += move_step_y;
}

void	move_backward(t_cub3d *cub3d)
{
	double	move_step_x;
	double	move_step_y;

	if (cub3d->player->is_sprint)
		cub3d->player->move_speed *= 1.5;
	move_step_x = -cub3d->player->dirx * cub3d->player->move_speed;
	move_step_y = -cub3d->player->diry * cub3d->player->move_speed;
	if (cub3d->map->grid[(int)(cub3d->player->posy)]
		[(int)(cub3d->player->posx + move_step_x)] == '0')
		cub3d->player->posx += move_step_x;
	if (cub3d->map->grid[(int)(cub3d->player->posy + move_step_y)]
		[(int)(cub3d->player->posx)] == '0')
		cub3d->player->posy += move_step_y;
}

void	move_left(t_cub3d *cub3d)
{
	double	move_step_x;
	double	move_step_y;

	if (cub3d->player->is_sprint)
		cub3d->player->move_speed *= 1.5;
	move_step_x = -cub3d->player->planex * cub3d->player->move_speed;
	move_step_y = -cub3d->player->planey * cub3d->player->move_speed;
	if (cub3d->map->grid[(int)(cub3d->player->posy)]
		[(int)(cub3d->player->posx + move_step_x)] == '0')
		cub3d->player->posx += move_step_x;
	if (cub3d->map->grid[(int)(cub3d->player->posy + move_step_y)]
		[(int)(cub3d->player->posx)] == '0')
		cub3d->player->posy += move_step_y;
}

void	move_right(t_cub3d *cub3d)
{
	double	move_step_x;
	double	move_step_y;

	if (cub3d->player->is_sprint)
		cub3d->player->move_speed *= 1.5;
	move_step_x = cub3d->player->planex * cub3d->player->move_speed;
	move_step_y = cub3d->player->planey * cub3d->player->move_speed;
	if (cub3d->map->grid[(int)(cub3d->player->posy)]
		[(int)(cub3d->player->posx + move_step_x)] == '0')
		cub3d->player->posx += move_step_x;
	if (cub3d->map->grid[(int)(cub3d->player->posy + move_step_y)]
		[(int)(cub3d->player->posx)] == '0')
		cub3d->player->posy += move_step_y;
}
