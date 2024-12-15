/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:05:33 by idomagal          #+#    #+#             */
/*   Updated: 2024/12/15 17:30:44 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/structs.h"

static int	is_door(t_cub3d *cub3d, int x, int y)
{
	if (y < 0 || y >= cub3d->map->height || x < 0 || x >= cub3d->map->width)
		return (0);
	if (cub3d->map->grid[y][x] == '2')
		return (1);
	return (0);
}

static void	assign_values(int *vars, int vals[4])
{
	vars[0] = vals[0];
	vars[1] = vals[1];
	vars[2] = vals[2];
	vars[3] = vals[3];
}

int	try_open_door(t_cub3d *cub3d)
{
	int	vars[4];
	int	dx[4];
	int	dy[4];
	int	i;

	vars[0] = (int)cub3d->player->posx;
	vars[1] = (int)cub3d->player->posy;
	assign_values(dx, (int [4]){1, -1, 0, 0});
	assign_values(dy, (int [4]){0, 0, 1, -1});
	i = 0;
	while (i < 4)
	{
		vars[2] = vars[0] + dx[i];
		vars[3] = vars[1] + dy[i];
		if (is_door(cub3d, vars[2], vars[3]))
		{
			cub3d->map->grid[vars[3]][vars[2]] = '0';
			open_existing_door(cub3d, vars[2], vars[3]);
			add_new_door(cub3d, vars[2], vars[3]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	update_doors(t_cub3d *cub3d)
{
	long	now;
	int		x;
	int		y;
	int		i;

	now = get_timestamp();
	i = 0;
	while (i < cub3d->door_count)
	{
		if (cub3d->doors[i].open && now - cub3d->doors[i].open_time > 5000)
		{
			x = cub3d->doors[i].x;
			y = cub3d->doors[i].y;
			if (y >= 0 && y < cub3d->map->height \
					&& x >= 0 && x < cub3d->map->width)
				cub3d->map->grid[y][x] = '2';
			cub3d->doors[i].open = 0;
		}
		i++;
	}
}
