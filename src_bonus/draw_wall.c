/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idomagal <idomagal@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:17:30 by idomagal          #+#    #+#             */
/*   Updated: 2024/12/16 16:17:33 by idomagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	find_tex(t_cub3d *cub3d, t_ray *ray)
{
	if (cub3d->map->grid[ray->mapy][ray->mapx] == '2')
		cub3d->c_tex = cub3d->sprites[8];
	else
	{
		if (ray->side == 0)
		{
			if (ray->raydirx > 0)
				cub3d->c_tex = cub3d->map->sprite_ea;
			else
				cub3d->c_tex = cub3d->map->sprite_we;
		}
		else
		{
			if (ray->raydiry > 0)
				cub3d->c_tex = cub3d->map->sprite_so;
			else
				cub3d->c_tex = cub3d->map->sprite_no;
		}
	}
}

double	get_wallx(t_ray *ray, t_cub3d *cub3d)
{
	double	wallx;

	if (ray->side == 0)
		wallx = cub3d->player->posy + ray->perpwalldist * ray->raydiry;
	else
		wallx = cub3d->player->posx + ray->perpwalldist * ray->raydirx;
	wallx -= floor(wallx);
	return (wallx);
}

static void	draw_wall_loop(t_cub3d *cub3d, int *int_vars, int *temp_vars)
{
	while (temp_vars[4] <= int_vars[3])
	{
		temp_vars[2] = (temp_vars[4] - int_vars[4])
			* 256 - cub3d->win_height * 128 + temp_vars[1] * 128;
		temp_vars[3] = ((temp_vars[2] * cub3d->c_tex->height)
				/ temp_vars[1]) / 256;
		if (temp_vars[0] < 0)
			temp_vars[0] = 0;
		if (temp_vars[0] >= cub3d->c_tex->width)
			temp_vars[0] = cub3d->c_tex->width - 1;
		if (temp_vars[3] < 0)
			temp_vars[3] = 0;
		if (temp_vars[3] >= cub3d->c_tex->height)
			temp_vars[3] = cub3d->c_tex->height - 1;
		put_pixel_to_img(cub3d->buffer, int_vars[0], temp_vars[4]++,
			get_pixel_color(cub3d->c_tex, temp_vars[0],
				temp_vars[3]));
	}
}

void	draw_wall(t_cub3d *cub3d, t_ray *ray, int *int_vars, double wallx)
{
	int	temp_vars[5];

	temp_vars[0] = (int)(wallx * (double)(cub3d->c_tex->width));
	temp_vars[1] = (int)(cub3d->win_height / ray->perpwalldist);
	int_vars[4] = (int)cub3d->player->pitch;
	int_vars[2] = -temp_vars[1] / 2 + cub3d->win_height / 2 + int_vars[4];
	if (int_vars[2] < 0)
		int_vars[2] = 0;
	int_vars[3] = temp_vars[1] / 2 + cub3d->win_height / 2 + int_vars[4];
	if (int_vars[3] >= cub3d->win_height)
		int_vars[3] = cub3d->win_height - 1;
	if (ray->side == 0 && ray->raydirx > 0)
		temp_vars[0] = cub3d->c_tex->width - temp_vars[0] - 1;
	if (ray->side == 1 && ray->raydiry < 0)
		temp_vars[0] = cub3d->c_tex->width - temp_vars[0] - 1;
	temp_vars[4] = 0;
	while (temp_vars[4] < int_vars[2])
		put_pixel_to_img(cub3d->buffer, int_vars[0],
			temp_vars[4]++, cub3d->map->ceiling);
	temp_vars[4] = int_vars[2];
	draw_wall_loop(cub3d, int_vars, temp_vars);
}
