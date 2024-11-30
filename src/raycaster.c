/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:06:50 by idomagal          #+#    #+#             */
/*   Updated: 2024/11/29 22:16:15 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

int get_pixel_color(t_sprite *sprite, int x, int y)
{
	int color;
	char *pixel;

	pixel = sprite->addr + (y * sprite->line_length + x * (sprite->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return color;
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
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (cub3d->player->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1.0 - cub3d->player->posx) * ray->deltadistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (cub3d->player->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1.0 - cub3d->player->posy) * ray->deltadisty;
	}
	return (0);
}

int	raycaster(t_cub3d *cub3d)
{
	t_ray	ray;
	for (int x = 0; x < cub3d->win_width; x++)
	{
		if (init_ray(&ray, cub3d, x))
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
			if (ray.mapx < 0 || ray.mapx >= cub3d->map->width ||
				ray.mapy < 0 || ray.mapy >= cub3d->map->height)
			{
				ray.hit = 1;
				break;
			}
			if (cub3d->map->grid[ray.mapy][ray.mapx] > '0') // Note: grid[y][x]
				ray.hit = 1;
		}
		if (ray.hit == 0)
			continue;
		if (ray.side == 0)
			ray.perpwalldist = (ray.sidedistx - ray.deltadistx);
		else
			ray.perpwalldist = (ray.sidedisty - ray.deltadisty);
		int lineheight = (int)(cub3d->win_height / ray.perpwalldist);
		int pitch = (int)cub3d->player->pitch;
		int drawstart = -lineheight / 2 + cub3d->win_height / 2 + pitch;
		if (drawstart < 0)
			drawstart = 0;
		int drawend = lineheight / 2 + cub3d->win_height / 2 + pitch;
		if (drawend >= cub3d->win_height)
			drawend = cub3d->win_height - 1;
		for (int y = 0; y < drawstart; y++)
			put_pixel_to_img(cub3d->buffer, x, y, cub3d->map->ceiling);
		int texnum;
		if (ray.side == 0)
		{
				if (ray.raydirx > 0)
					texnum = 2; // EAST
				else
					texnum = 3; // WEST
		}
		else
		{
				if (ray.raydiry > 0)
					texnum = 1; // SOUTH
				else
					texnum = 0; // NORTH
		}
		double wallx;
		if (ray.side == 0)
			wallx = cub3d->player->posy + ray.perpwalldist * ray.raydiry;
		else
			wallx = cub3d->player->posx + ray.perpwalldist * ray.raydirx;
		wallx -= floor(wallx);
		int texx = (int)(wallx * (double)(cub3d->sprites[texnum]->width));
		if (ray.side == 0 && ray.raydirx > 0)
			texx = cub3d->sprites[texnum]->width - texx - 1;
		if (ray.side == 1 && ray.raydiry < 0)
			texx = cub3d->sprites[texnum]->width - texx - 1;
		for (int y = drawstart; y < drawend; y++)
		{
			int d = (y - pitch) * 256 - cub3d->win_height * 128 + lineheight * 128;
			int texy = ((d * cub3d->sprites[texnum]->height) / lineheight) / 256;
			if (texx < 0)
				texx = 0;
			if (texx >= cub3d->sprites[texnum]->width)
				texx = cub3d->sprites[texnum]->width - 1;
			if (texy < 0)
				texy = 0;
			if (texy >= cub3d->sprites[texnum]->height)
				texy = cub3d->sprites[texnum]->height - 1;
			int color = get_pixel_color(cub3d->sprites[texnum], texx, texy);
			put_pixel_to_img(cub3d->buffer, x, y, color);
		}
		double rayDirX0 = cub3d->player->dirx - cub3d->player->planex;
		double rayDirY0 = cub3d->player->diry - cub3d->player->planey;
		double rayDirX1 = cub3d->player->dirx + cub3d->player->planex;
		double rayDirY1 = cub3d->player->diry + cub3d->player->planey;
		for (int y = drawend + 1; y < cub3d->win_height; y++)
		{
			int currentY = y - cub3d->win_height / 2 - pitch;
			double posZ = 0.5 * cub3d->win_height;
			double rowDistance = posZ / currentY;
			double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / cub3d->win_width;
			double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / cub3d->win_width;
			double floorX = cub3d->player->posx + rowDistance * rayDirX0;
			double floorY = cub3d->player->posy + rowDistance * rayDirY0;
			floorX += floorStepX * x;
			floorY += floorStepY * x;
			int floorTexX = (int)(floorX * cub3d->sprites[FLOOR]->width) % cub3d->sprites[FLOOR]->width;
			int floorTexY = (int)(floorY * cub3d->sprites[FLOOR]->height) % cub3d->sprites[FLOOR]->height;
			if (floorTexX < 0)
				floorTexX += cub3d->sprites[FLOOR]->width;
			if (floorTexY < 0)
				floorTexY += cub3d->sprites[FLOOR]->height;
			int floorColor = get_pixel_color(cub3d->sprites[FLOOR], floorTexX, floorTexY);
			put_pixel_to_img(cub3d->buffer, x, y, floorColor);
		}
		for (int y = 0; y < drawstart; y++)
		{
			int currentY = y - cub3d->win_height / 2 - pitch;
			double posZ = 0.5 * cub3d->win_height;
			double rowDistance = posZ / -currentY;
			double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / cub3d->win_width;
			double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / cub3d->win_width;
			double floorX = cub3d->player->posx + rowDistance * rayDirX0;
			double floorY = cub3d->player->posy + rowDistance * rayDirY0;
			floorX += floorStepX * x;
			floorY += floorStepY * x;
			int ceilTexX = (int)(floorX * cub3d->sprites[CEILING]->width) % cub3d->sprites[CEILING]->width;
			int ceilTexY = (int)(floorY * cub3d->sprites[CEILING]->height) % cub3d->sprites[CEILING]->height;
			if (ceilTexX < 0)
				ceilTexX += cub3d->sprites[CEILING]->width;
			if (ceilTexY < 0)
				ceilTexY += cub3d->sprites[CEILING]->height;
			int ceilColor = get_pixel_color(cub3d->sprites[CEILING], ceilTexX, ceilTexY);
			put_pixel_to_img(cub3d->buffer, x, y, ceilColor);
		}

	}

	ft_draw_minimap(cub3d, cub3d->player->posx, cub3d->player->posy);
	cub3d->frame++;
	return (0);
}
