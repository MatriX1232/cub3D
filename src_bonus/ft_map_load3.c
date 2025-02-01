/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_load3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:09:07 by msolinsk          #+#    #+#             */
/*   Updated: 2025/01/30 19:57:02 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_north_south(t_player *player, char direction)
{
	if (direction == 'N')
	{
		player->dirx = 0;
		player->diry = -1;
		player->planex = 0.66;
		player->planey = 0;
	}
	else if (direction == 'S')
	{
		player->dirx = 0;
		player->diry = 1;
		player->planex = -0.66;
		player->planey = 0;
	}
}

void	ft_east_west(t_player *player, char direction)
{
	if (direction == 'E')
	{
		player->dirx = 1;
		player->diry = 0;
		player->planex = 0;
		player->planey = 0.66;
	}
	else if (direction == 'W')
	{
		player->dirx = -1;
		player->diry = 0;
		player->planex = 0;
		player->planey = -0.66;
	}
}

void	ft_set_player_position(t_player *player, int x, int y, char **grid)
{
	grid[y][x] = '0';
	player->posx = x + 0.5;
	player->posy = y + 0.5;
}

void	ft_load_texture(t_cub3d *cub3d, t_map *map, char **split, int index)
{
	if (index == 0)
		map->sprite_no = xpm_load_image(cub3d->mlx, split[1], 1);
	else if (index == 1)
		map->sprite_so = xpm_load_image(cub3d->mlx, split[1], 1);
	else if (index == 2)
		map->sprite_we = xpm_load_image(cub3d->mlx, split[1], 1);
	else if (index == 3)
		map->sprite_ea = xpm_load_image(cub3d->mlx, split[1], 1);
	cub3d->parsed_elements++;
}

void	ft_load_color(t_cub3d *cub3d, t_map *map, char **split, int index)
{
	char	**split_rgb;

	split_rgb = ft_split(split[1], ',');
	if (index == 5)
		map->floor = (int)rgb_to_hex(ft_atoi(split_rgb[0]),
				ft_atoi(split_rgb[1]), ft_atoi(split_rgb[2]));
	else if (index == 6)
		map->ceiling = (int)rgb_to_hex(ft_atoi(split_rgb[0]),
				ft_atoi(split_rgb[1]), ft_atoi(split_rgb[2]));
	ft_free_2d_array(split_rgb);
	cub3d->parsed_elements++;
}
