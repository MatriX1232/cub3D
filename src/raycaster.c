/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idomagal <idomagal@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:06:50 by idomagal          #+#    #+#             */
/*   Updated: 2024/11/21 15:06:50 by idomagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	init_ray(t_ray *ray, t_cub3d *cub3d, int x)
{
	ray->camerax = 2 * x / (double)cub3d->w - 1;
	ray->raydirx = cub3d->player.dirx + cub3d->player.planex * ray->camerax;
	ray->raydiry = cub3d->player.diry + cub3d->player.planey * ray->camerax;
	ray->mapx = (int)cub3d->player.posx;
	ray->mapy = (int)cub3d->player.posy;
	if (ray->raydirx == 0)
		ray->deltadistx = 1e30;
	else
		ray->deltadistx = fabs(1 / ray->raydirx);
	if (ray->raydiry == 0)
		ray->deltadisty = 1e30;
	else
		ray->deltadisty = fabs(1 / ray->raydiry);
	ray->hit = 0;
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (cub3d->player.posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - cub3d->player.posx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (cub3d->player.posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - cub3d->player.posy) * ray->deltadisty;
	}
	return (0);
}

int	raycaster(t_cub3d *cub3d)
{
	t_ray	ray;

	for (int x = 0; x < cub3d->w; x++)
	{
		if (init_ray(&ray, cub3d))
			return (1);
		while (ray.hit == 0)
		{
			if (ray.sidedistx < ray.sidedisty)
			{
				ray.sidedistx += ray.deltadistx;
				ray.mapx += ray.stepx;
				ray.side = 0;
			}
			else
			{
				ray.sidedisty += ray.deltadisty;
				ray.mapy += ray.stepy;
				ray.side = 1;
			}
			if (cub3d->map.map[ray.mapx][ray.mapy] > 0)
				ray.hit = 1;
		}
		if (ray.side == 0)
			ray.perpwalldist = (ray.sidedistx - ray.deltadistx);
		else
			ray.perpwalldist = (ray.sidedisty - ray.deltadisty);
		int lineheight = (int)(cub3d->h / ray.perpwalldist);
		int pitch = 100;
		int drawstart = -lineheight / 2 + cub3d->h / 2 + pitch;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + cub3d->h / 2 + pitch;
		if (drawend >= cub3d->h)
			drawend = cub3d->h - 1;
		int texnum = cub3d->map.map[ray.mapx][ray.mapy] - 1;
		double wallx;
		if (ray.side == 0)
			wallx = cub3d->player.posy + ray.perpwalldist * ray.raydiry;
		else
			wallx = cub3d->player.posx + ray.perpwalldist * ray.raydirx;
		wallx -= floor(wallx);
		int texx = int(wallx * double(texwidth));
		if (ray.side == 0 && ray.raydirx > 0)
			texx = texwidth - texx - 1;
		if (ray.side == 1 && ray.raydiry < 0)
			texx = texwidth - texx - 1;
	}
}