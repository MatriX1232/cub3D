/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:06:50 by idomagal          #+#    #+#             */
/*   Updated: 2024/11/29 00:59:30 by msolinsk         ###   ########.fr       */
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
		int pitch = 0;
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
		for (int y = drawend; y < cub3d->win_height; y++)
			put_pixel_to_img(cub3d->buffer, x, y, cub3d->map->floor);
	}
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->buffer->img, 0, 0);
	ft_draw_minimap(cub3d, cub3d->player->posx, cub3d->player->posy);
	cub3d->frame++;
	if (FRAME_RATE >= 0)
	{
		char *fps_str;
		int fps;
		float frame_time;

		frame_time = (get_timestamp() - cub3d->prev_time) / 1000.0;
		fps = (int)(1.0 / frame_time);
		fps_str = ft_itoa(fps);
		mlx_string_put(cub3d->mlx, cub3d->win, 10, 10, 0xFFFFFF, "FPS:");
		mlx_string_put(cub3d->mlx, cub3d->win, 50, 10, 0xFFFFFF, fps_str);
		free(fps_str);
		cub3d->prev_time = get_timestamp();
		usleep(1000000 / (FRAME_RATE * 1.4));
	}
	return (0);
}
