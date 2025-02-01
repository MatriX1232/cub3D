/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_load2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:08:14 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/15 18:17:49 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_process_grid(t_cub3d *cub3d, t_map *map, char *line, int y)
{
	t_player	*player;
	int			x;

	player = cub3d->player;
	map->grid[y] = ft_strdup(line);
	if (!map->grid[y])
		ft_log("Cannot allocate memory for map grid", NULL, 3);
	x = 0;
	while (line[x])
	{
		if (line[x] == 'N' || line[x] == 'S' || \
			line[x] == 'E' || line[x] == 'W')
		{
			if (line[x] == 'N' || line[x] == 'S')
				ft_north_south(player, line[x]);
			else if (line[x] == 'E' || line[x] == 'W')
				ft_east_west(player, line[x]);
			ft_set_player_position(player, x, y, map->grid);
			cub3d->player->amount++;
		}
		x++;
	}
	if ((int)ft_strlen(line) > map->width)
		map->width = ft_strlen(line);
}
