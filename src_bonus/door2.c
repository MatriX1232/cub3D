/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:06:27 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/15 17:31:30 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/structs.h"

void	init_door_system(t_cub3d *cub3d)
{
	int	i;

	cub3d->door_count = 0;
	i = 0;
	while (i < MAX_DOORS)
	{
		cub3d->doors[i].x = 0;
		cub3d->doors[i].y = 0;
		cub3d->doors[i].open = 0;
		cub3d->doors[i].open_time = 0;
		i++;
	}
}

void	open_existing_door(t_cub3d *cub3d, int nx, int ny)
{
	int	j;

	j = 0;
	while (j < cub3d->door_count)
	{
		if (cub3d->doors[j].x == nx && cub3d->doors[j].y == ny)
		{
			cub3d->doors[j].open = 1;
			cub3d->doors[j].open_time = get_timestamp();
			return ;
		}
		j++;
	}
}

void	add_new_door(t_cub3d *cub3d, int nx, int ny)
{
	if (cub3d->door_count < MAX_DOORS)
	{
		cub3d->doors[cub3d->door_count].x = nx;
		cub3d->doors[cub3d->door_count].y = ny;
		cub3d->doors[cub3d->door_count].open = 1;
		cub3d->doors[cub3d->door_count].open_time = get_timestamp();
		cub3d->door_count++;
	}
}
