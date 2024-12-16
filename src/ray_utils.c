/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idomagal <idomagal@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 16:17:19 by idomagal          #+#    #+#             */
/*   Updated: 2024/12/16 16:17:23 by idomagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

static void	init_ray2(t_ray *ray, t_cub3d *cub3d)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (cub3d->player->posx - ray->mapx)
			* ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - cub3d->player->posx)
			* ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (cub3d->player->posy - ray->mapy)
			* ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - cub3d->player->posy)
			* ray->deltadisty;
	}
}

int	init_ray(t_ray *ray, t_cub3d *cub3d, int x)
{
	ray->camerax = 2 * x / (double)cub3d->win_width - 1;
	ray->raydirx = cub3d->player->dirx + cub3d->player->planex * ray->camerax;
	ray->raydiry = cub3d->player->diry + cub3d->player->planey * ray->camerax;
	ray->mapx = (int)cub3d->player->posx;
	ray->mapy = (int)cub3d->player->posy;
	if (ray->raydirx == 0)
		ray->deltadistx = 1e30;
	else
		ray->deltadistx = fabs(1 / ray->raydirx);
	if (ray->raydiry == 0)
		ray->deltadisty = 1e30;
	else
		ray->deltadisty = fabs(1 / ray->raydiry);
	ray->hit = 0;
	init_ray2(ray, cub3d);
	return (0);
}

void	cast_ray(t_cub3d *cub3d, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (ray->mapx < 0 || ray->mapx >= cub3d->map->width
			|| ray->mapy < 0 || ray->mapy >= cub3d->map->height)
		{
			ray->hit = 1;
			break ;
		}
		if (cub3d->map->grid[ray->mapy][ray->mapx] > '0')
			ray->hit = 1;
	}
}

void	perpwalldist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
}
