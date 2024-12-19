/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:09:19 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/19 18:55:08 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

static int	ft_check_neighbour(t_map *map, int x, int y)
{
	if (x - 1 < 0 || (map->grid[y][x - 1] != '0' && \
		map->grid[y][x - 1] != '1' && map->grid[y][x - 1] != ' ') ||
		y - 1 < 0 || (map->grid[y - 1][x] != '0' && \
		map->grid[y - 1][x] != '1' && map->grid[y - 1][x] != ' ') || \
		x + 1 >= (int)ft_strlen(map->grid[y]) || \
		(map->grid[y][x + 1] != '0' && \
		map->grid[y][x + 1] != '1' && map->grid[y][x + 1] != ' ') || \
		y + 1 >= map->height || (map->grid[y + 1][x] != '0' && \
		map->grid[y + 1][x] != '1' && map->grid[y + 1][x] != ' '))
	{
		return (1);
	}
	return (0);
	{
		return (1);
	}
	return (0);
}

int	ft_check_map_closed(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (map->grid[y][x] == '0')
			{
				if (ft_check_neighbour(map, x, y) != 0)
				{
					ft_log("Map is not closed.", NULL, 3);
					return (1);
				}
			}
			x++;
		}
		printf("\n");
		y++;
	}
	return (0);
}
