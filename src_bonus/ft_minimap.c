/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minimap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:25:21 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/04 15:21:39 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

static void	ft_draw_scale(t_cub3d *cub3d, int x, int y, int color)
{
	int	i;
	int	j;
	int	offx;
	int	offy;
	int	s;

	offx = (cub3d->win_width - (cub3d->map->width * MINIMAP_SCALE)) - 10;
	offy = 10;
	i = 0;
	s = MINIMAP_SCALE;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			put_pixel_to_img(cub3d->buffer, \
				offx + (x * s) + i, \
				offy + (y * s) + j, \
				color);
			j++;
		}
		i++;
	}
}

static void	custom_switch(t_cub3d *cub3d, int x, int y)
{
	if (cub3d->map->grid[y][x] == '0' || cub3d->map->grid[y][x] == '2')
		ft_draw_scale(cub3d, x, y, MINIMAP_BG);
	else if (cub3d->map->grid[y][x] == '1')
		ft_draw_scale(cub3d, x, y, MINIMAP_FG);
}

void	ft_draw_minimap(t_cub3d *cub3d, int px, int py)
{
	int	x;
	int	y;

	if (!cub3d->map || !cub3d->map->grid)
		return (ft_log("Map or Grid is NULL", NULL, 2));
	if (cub3d->map->width <= 0 || cub3d->map->height <= 0)
		return (ft_log("Map width or height is <= 0", NULL, 2));
	x = 0;
	while (x < cub3d->map->width)
	{
		y = 0;
		while (y < cub3d->map->height)
		{
			if (cub3d->map->grid[y] && x < \
				(int)ft_strlen(cub3d->map->grid[y]) && cub3d->map->grid[y][x])
			{
				custom_switch(cub3d, x, y);
				if (x == px && y == py)
					ft_draw_scale(cub3d, x, y, 0xFF0000);
			}
			y++;
		}
		x++;
	}
}
