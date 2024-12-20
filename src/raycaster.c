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

int	raycaster(t_cub3d *cub3d)
{
	double	wallx;
	t_ray	ray;
	int		int_vars[5];

	int_vars[0] = 0;
	while (int_vars[0] < cub3d->win_width)
	{
		if (init_ray(&ray, cub3d, int_vars[0]))
			return (1);
		cast_ray(cub3d, &ray);
		if (ray.hit == 0)
			continue ;
		perpwalldist(&ray);
		find_tex(cub3d, &ray);
		wallx = get_wallx(&ray, cub3d);
		draw_wall(cub3d, &ray, int_vars, wallx);
		draw_ceil_floor(cub3d, int_vars);
		int_vars[0]++;
	}
	cub3d->frame++;
	return (0);
}
