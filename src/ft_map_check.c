/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:09:19 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/20 15:51:26 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

static int	ft_check_neighbour(t_map *map, int x, int y)
{
	if (map->grid[y + 1][x + 1] == '\0' || map->grid[y - 1] == NULL || \
		map->grid[y][x + 1] == '\0')
	{
		return (1);
	}
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
}

int	ft_check_if_map_valid(t_cub3d *cub3d, t_map *map)
{
	if (cub3d->checked_elements != cub3d->parsed_elements)
	{
		ft_log("Incorrect number of elements.", NULL, 3);
		return (1);
	}
	if (!map)
		return (ft_log("Map structure is NULL.", NULL, 3), 1);
	if (!map->grid)
		return (ft_log("Map grid is NULL.", NULL, 3), 1);
	if (map->height <= 0)
		return (ft_log("Map height is invalid.", NULL, 3), 1);
	if (map->width <= 0)
		return (ft_log("Map width is invalid.", NULL, 3), 1);
	if (!map->sprite_no || !map->sprite_no || \
		!map->sprite_ea || !map->sprite_we)
		return (ft_log("One or more textures failed to load.", NULL, 3), 1);
	if (map->floor == -1 || map->ceiling == -1)
		return (ft_log("One or more colors failed to load.", NULL, 3), 1);
	if (cub3d->map_error)
		return (ft_log("Something is wrong with the map bruh", NULL, 3), 1);
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
		y++;
	}
	return (0);
}
