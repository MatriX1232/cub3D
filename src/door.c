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

int try_open_door(t_cub3d *cub3d)
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
		if (ny >= 0 && ny < cub3d->map->height && nx >= 0 && nx < cub3d->map->width)
		{
			if (cub3d->map->grid[ny][nx] == '2')
			{
				cub3d->map->grid[ny][nx] = '0';
				cub3d->door_x = nx;
				cub3d->door_y = ny;
				cub3d->door_opened_time = get_timestamp();
				cub3d->door_is_open = 1;
				return (1);
			}
		}
	}
	return (0);
}

void update_doors(t_cub3d *cub3d)
{
	if (cub3d->door_is_open)
	{
		long now = get_timestamp();
		if (now - cub3d->door_opened_time > 5000)
		{
			if (cub3d->door_y >= 0 && cub3d->door_y < cub3d->map->height &&
				cub3d->door_x >= 0 && cub3d->door_x < cub3d->map->width)
				cub3d->map->grid[cub3d->door_y][cub3d->door_x] = '2';
			cub3d->door_is_open = 0;
		}
	}
}

