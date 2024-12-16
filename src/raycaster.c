/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:06:50 by idomagal          #+#    #+#             */
/*   Updated: 2024/12/04 12:10:01 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

int	get_pixel_color(t_sprite *sprite, int x, int y)
{
	int		color;
	char	*pixel;

	pixel = sprite->addr + (y * sprite->line_length
			+ x * (sprite->bits_per_pixel / 8));
	color = *(unsigned int *)pixel;
	return (color);
}

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

static void	cast_ray(t_cub3d *cub3d, t_ray *ray)
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

static void	perpwalldist(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedistx - ray->deltadistx);
	else
		ray->perpwalldist = (ray->sidedisty - ray->deltadisty);
}

static int	find_texnum(t_cub3d *cub3d, t_ray *ray)
{
	int	texnum;

	if (cub3d->map->grid[ray->mapy][ray->mapx] == '2')
		texnum = 8;
	else
	{
		if (ray->side == 0)
		{
			if (ray->raydirx > 0)
				texnum = 2;
			else
				texnum = 3;
		}
		else
		{
			if (ray->raydiry > 0)
				texnum = 1;
			else
				texnum = 0;
		}
	}
	return (texnum);
}

static double	get_wallx(t_ray *ray, t_cub3d *cub3d)
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
	while (temp_vars[4] < int_vars[3])
	{
		temp_vars[2] = (temp_vars[4] - int_vars[4])
			* 256 - cub3d->win_height * 128 + temp_vars[1] * 128;
		temp_vars[3] = ((temp_vars[2] * cub3d->sprites[int_vars[1]]->height)
				/ temp_vars[1]) / 256;
		if (temp_vars[0] < 0)
			temp_vars[0] = 0;
		if (temp_vars[0] >= cub3d->sprites[int_vars[1]]->width)
			temp_vars[0] = cub3d->sprites[int_vars[1]]->width - 1;
		if (temp_vars[3] < 0)
			temp_vars[3] = 0;
		if (temp_vars[3] >= cub3d->sprites[int_vars[1]]->height)
			temp_vars[3] = cub3d->sprites[int_vars[1]]->height - 1;
		put_pixel_to_img(cub3d->buffer, int_vars[0], temp_vars[4]++,
			get_pixel_color(cub3d->sprites[int_vars[1]], temp_vars[0],
				temp_vars[3]));
	}
}

static void	draw_wall(t_cub3d *cub3d, t_ray *ray, int *int_vars, double wallx)
{
	int	temp_vars[5]; // 0 = texx, 1 = lineheight, 2 = d, 3 = texy, 4 = y
	temp_vars[0] = (int)(wallx * (double)(cub3d->sprites[int_vars[1]]->width));
	temp_vars[1] = (int)(cub3d->win_height / ray->perpwalldist);
	int_vars[4] = (int)cub3d->player->pitch;
	int_vars[2] = -temp_vars[1] / 2 + cub3d->win_height / 2 + int_vars[4];
	if (int_vars[2] < 0)
		int_vars[2] = 0;
	int_vars[3] = temp_vars[1] / 2 + cub3d->win_height / 2 + int_vars[4];
	if (int_vars[3] >= cub3d->win_height)
		int_vars[3] = cub3d->win_height - 1;
	if (ray->side == 0 && ray->raydirx > 0)
		temp_vars[0] = cub3d->sprites[int_vars[1]]->width - temp_vars[0] - 1;
	if (ray->side == 1 && ray->raydiry < 0)
		temp_vars[0] = cub3d->sprites[int_vars[1]]->width - temp_vars[0] - 1;
	temp_vars[4] = 0;
	while (temp_vars[4] < int_vars[2])
		put_pixel_to_img(cub3d->buffer, int_vars[0],
			temp_vars[4]++, cub3d->map->ceiling); // could be bugging
	temp_vars[4] = int_vars[2];
	draw_wall_loop(cub3d, int_vars, temp_vars);
}

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
	double	double_vars[5]; // 0 = rowDistance, 1 = floorStepX, 2 = floorStepY, 3 = floorX, 4 = floorY
	int			temp_int_vars[2]; // 0 = floorTexX, 1 = floorTexY
	int		y;

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
	double	double_vars[5]; // 0 = rowDistance, 1 = floorStepX, 2 = floorStepY, 3 = floorX, 4 = floorY
	int		temp_int_vars[2]; // 0 = ceilTexX, 1 = ceilTexY
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

static void	draw_ceil_floor(t_cub3d *cub3d, int *int_vars)
{
	double	temp_vars[4]; // 0 = rayDirX0, 1 = rayDirY0, 2 = rayDirX1, 3 = rayDirY1
	temp_vars[0] = cub3d->player->dirx - cub3d->player->planex;
	temp_vars[1] = cub3d->player->diry - cub3d->player->planey;
	temp_vars[2] = cub3d->player->dirx + cub3d->player->planex;
	temp_vars[3] = cub3d->player->diry + cub3d->player->planey;
	draw_ceil(cub3d, int_vars, temp_vars);
	draw_floor(cub3d, int_vars, temp_vars);
}

int	raycaster(t_cub3d *cub3d)
{
	double	wallx;
	t_ray		ray;
	int		int_vars[5]; // 0 = x, 1 = texnum, 2 = drawstart, 3 = drawend, 4 = pitch
	int_vars[0] = 0;
	while (int_vars[0] < cub3d->win_width)
	{
		if (init_ray(&ray, cub3d, int_vars[0]))
			return (1);
		cast_ray(cub3d, &ray);
		if (ray.hit == 0)
			continue ;
		perpwalldist(&ray);
		int_vars[1] = find_texnum(cub3d, &ray);
		wallx = get_wallx(&ray, cub3d);
		draw_wall(cub3d, &ray, int_vars, wallx);
		draw_ceil_floor(cub3d, int_vars);
		int_vars[0]++;
	}
	ft_draw_minimap(cub3d, cub3d->player->posx, cub3d->player->posy);
	cub3d->frame++;
	return (0);
}
