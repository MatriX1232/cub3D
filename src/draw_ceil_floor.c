/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ceil_floor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idomagal <idomagal@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:17:26 by idomagal          #+#    #+#             */
/*   Updated: 2024/12/16 16:17:28 by idomagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

static void	init_floor_vars(t_cub3d *cub3d, int *int_vars,
	double *temp_vars, double *double_vars)
{
	double_vars[1] = double_vars[0]
		* (temp_vars[2] - temp_vars[0]) / cub3d->win_width;
	double_vars[2] = double_vars[0]
		* (temp_vars[3] - temp_vars[1]) / cub3d->win_width;
	double_vars[3] = cub3d->player->posx + double_vars[0] * temp_vars[0];
	double_vars[4] = cub3d->player->posy + double_vars[0] * temp_vars[1];
	double_vars[3] += double_vars[1] * int_vars[0];
	double_vars[4] += double_vars[2] * int_vars[0];
}

static void	draw_floor(t_cub3d *cub3d, int *int_vars, double *temp_vars)
{
	int			temp_int_vars[2];
	int			y;
	double		double_vars[5];

	y = int_vars[3] + 1;
	while (y < cub3d->win_height)
	{
		double_vars[0] = (0.5 * cub3d->win_height)
			/ (int)(y - cub3d->win_height / 2 - int_vars[4]);
		init_floor_vars(cub3d, int_vars, temp_vars, double_vars);
		temp_int_vars[0] = (int)(double_vars[3]
				* cub3d->sprites[FLOOR]->width) % cub3d->sprites[FLOOR]->width;
		temp_int_vars[1] = (int)(double_vars[4]
				* cub3d->sprites[FLOOR]->height)
			% cub3d->sprites[FLOOR]->height;
		if (temp_int_vars[0] < 0)
			temp_int_vars[0] += cub3d->sprites[FLOOR]->width;
		if (temp_int_vars[1] < 0)
			temp_int_vars[1] += cub3d->sprites[FLOOR]->height;
		put_pixel_to_img(cub3d->buffer, int_vars[0], y,
			get_pixel_color(cub3d->sprites[FLOOR],
				temp_int_vars[0], temp_int_vars[1]));
		y++;
	}
}

static void	init_ceil_vars(t_cub3d *cub3d, int *int_vars,
	double *temp_vars, double *double_vars)
{
	double_vars[1] = double_vars[0]
		* (temp_vars[2] - temp_vars[0]) / cub3d->win_width;
	double_vars[2] = double_vars[0]
		* (temp_vars[3] - temp_vars[1]) / cub3d->win_width;
	double_vars[3] = cub3d->player->posx + double_vars[0] * temp_vars[0];
	double_vars[4] = cub3d->player->posy + double_vars[0] * temp_vars[1];
	double_vars[3] += double_vars[1] * int_vars[0];
	double_vars[4] += double_vars[2] * int_vars[0];
}

static void	draw_ceil(t_cub3d *cub3d, int *int_vars, double *temp_vars)
{
	double	double_vars[5];
	int		temp_int_vars[2];
	int		y;

	y = 0;
	while (y < int_vars[2])
	{
		double_vars[0] = (0.5 * cub3d->win_height)
			/ -(int)(y - cub3d->win_height / 2 - int_vars[4]);
		init_ceil_vars(cub3d, int_vars, temp_vars, double_vars);
		temp_int_vars[0] = (int)(double_vars[3]
				* cub3d->sprites[CEILING]->width)
			% cub3d->sprites[CEILING]->width;
		temp_int_vars[1] = (int)(double_vars[4]
				* cub3d->sprites[CEILING]->height)
			% cub3d->sprites[CEILING]->height;
		if (temp_int_vars[0] < 0)
			temp_int_vars[0] += cub3d->sprites[CEILING]->width;
		if (temp_int_vars[1] < 0)
			temp_int_vars[1] += cub3d->sprites[CEILING]->height;
		put_pixel_to_img(cub3d->buffer, int_vars[0], y,
			get_pixel_color(cub3d->sprites[CEILING],
				temp_int_vars[0], temp_int_vars[1]));
		y++;
	}
}

void	draw_ceil_floor(t_cub3d *cub3d, int *int_vars)
{
	double	temp_vars[4];

	temp_vars[0] = cub3d->player->dirx - cub3d->player->planex;
	temp_vars[1] = cub3d->player->diry - cub3d->player->planey;
	temp_vars[2] = cub3d->player->dirx + cub3d->player->planex;
	temp_vars[3] = cub3d->player->diry + cub3d->player->planey;
	draw_ceil(cub3d, int_vars, temp_vars);
	draw_floor(cub3d, int_vars, temp_vars);
}
