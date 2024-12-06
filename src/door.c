/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idomagal <idomagal@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:05:33 by idomagal          #+#    #+#             */
/*   Updated: 2024/12/06 12:05:38 by idomagal         ###   ########.fr       */
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

void	init_door_system(t_cub3d *cub3d)
{
	int i;

	cub3d->door_count = 0;
	for (i = 0; i < MAX_DOORS; i++)
	{
		cub3d->doors[i].x = 0;
		cub3d->doors[i].y = 0;
		cub3d->doors[i].open = 0;
		cub3d->doors[i].open_time = 0;
	}
}

int	try_open_door(t_cub3d *cub3d)
{
	int px = (int)cub3d->player->posx;
	int py = (int)cub3d->player->posy;
	int dx[4] = {1, -1, 0, 0};
	int dy[4] = {0, 0, 1, -1};
	int i;
	for (i = 0; i < 4; i++)
	{
		int nx = px + dx[i];
		int ny = py + dy[i];
		if (is_door(cub3d, nx, ny))
		{
			cub3d->map->grid[ny][nx] = '0';
			int j;
			int found = 0;
			for (j = 0; j < cub3d->door_count; j++)
			{
				if (cub3d->doors[j].x == nx && cub3d->doors[j].y == ny)
				{
					cub3d->doors[j].open = 1;
					cub3d->doors[j].open_time = get_timestamp();
					found = 1;
					break;
				}
			}
			if (!found && cub3d->door_count < MAX_DOORS)
			{
				cub3d->doors[cub3d->door_count].x = nx;
				cub3d->doors[cub3d->door_count].y = ny;
				cub3d->doors[cub3d->door_count].open = 1;
				cub3d->doors[cub3d->door_count].open_time = get_timestamp();
				cub3d->door_count++;
			}
			return (1);
		}
	}
	return (0);
}

void update_doors(t_cub3d *cub3d)
{
	long now = get_timestamp();
	int i;

	for (i = 0; i < cub3d->door_count; i++)
	{
		if (cub3d->doors[i].open && now - cub3d->doors[i].open_time > 5000)
		{
			int x = cub3d->doors[i].x;
			int y = cub3d->doors[i].y;
			if (y >= 0 && y < cub3d->map->height && x >= 0 && x < cub3d->map->width)
				cub3d->map->grid[y][x] = '2';
			cub3d->doors[i].open = 0;
		}
	}
}
