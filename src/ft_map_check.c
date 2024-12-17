/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:09:19 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/17 11:36:32 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

int ft_check_map_closed(t_map *map)
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
				if (x - 1 < 0 || map->grid[y][x - 1] == ' ' ||
					y - 1 < 0 || map->grid[y - 1][x] == ' ' ||
					x + 1 >= (int)ft_strlen(map->grid[y]) || map->grid[y][x + 1] == ' ' ||
					y + 1 >= map->height || map->grid[y + 1][x] == ' ')
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

// int	ft_check_map_closed(t_map *map)
// {
// 	int	x;
// 	int	y;

// 	// Check top and bottom borders
// 	for (x = 0; x < map->width; x++)
// 	{
// 		if (x >= (int)ft_strlen(map->grid[0]) || (map->grid[0][x] != '1' && map->grid[0][x] != ' '))
// 		{
// 			ft_log("Map is not closed.", NULL, 3);
// 			return (0);
// 		}
// 		if (x >= (int)ft_strlen(map->grid[map->height - 1]) || (map->grid[map->height - 1][x] != '1' && map->grid[map->height - 1][x] != '0'))
// 		{
// 			ft_log("Map is not closed.", NULL, 3);
// 			return (0);
// 		}
// 	}

// 	// Check left and right borders
// 	for (y = 0; y < map->height; y++)
// 	{
// 		if (map->grid[y][0] != '1' || map->grid[y][ft_strlen(map->grid[y]) - 1] != '1')
// 		{
// 			ft_log("Map is not closed.", NULL, 3);
// 			return (0);
// 		}
// 	}

// 	// Check the interior of the map
// 	for (y = 1; y < map->height - 1; y++)
// 	{
// 		for (x = 1; x < map->width - 1; x++)
// 		{
// 			if (x >= (int)ft_strlen(map->grid[y]))
// 				continue;
// 			if (map->grid[y][x] == '0')
// 			{
// 				if ((x - 1 >= (int)ft_strlen(map->grid[y - 1]) || map->grid[y - 1][x] != '1') ||
// 					(x - 1 >= (int)ft_strlen(map->grid[y + 1]) || map->grid[y + 1][x] != '1') ||
// 					(map->grid[y][x - 1] != '1') ||
// 					(x + 1 >= (int)ft_strlen(map->grid[y]) || map->grid[y][x + 1] != '1'))
// 				{
// 					ft_log("Map is not closed.", NULL, 3);
// 					return (0);
// 				}
// 			}
// 		}
// 	}

// 	return (1);
// }