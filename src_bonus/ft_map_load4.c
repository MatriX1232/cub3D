/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_load4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:13:30 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/19 23:34:01 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_replace_spaces(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->grid[i])
	{
		j = 0;
		while (map->grid[i][j])
		{
			if (map->grid[i][j] == ' ')
				map->grid[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	ft_get_map_height(char *path)
{
	int		fd;
	char	*line;
	int		height;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_log("Cannot open file", path, 3), 0);
	height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

int	ft_handle_split(t_map *map, char **split, t_cub3d *cub3d)
{
	int	index;

	index = -1;
	if (ft_strncmp("NO", split[0], 3) == 0 && map->sprite_no == NULL)
		index = 0;
	if (ft_strncmp("SO", split[0], 3) == 0 && map->sprite_so == NULL)
		index = 1;
	if (ft_strncmp("WE", split[0], 3) == 0 && map->sprite_we == NULL)
		index = 2;
	if (ft_strncmp("EA", split[0], 3) == 0 && map->sprite_ea == NULL)
		index = 3;
	if (ft_strncmp("F", split[0], 2) == 0 && map->floor == -1)
		index = 5;
	if (ft_strncmp("C", split[0], 2) == 0 && map->ceiling == -1)
		index = 6;
	if (index == -1)
		return (1);
	if (index < 4)
		ft_load_texture(cub3d, map, split, index);
	else
		ft_load_color(map, split, index);
	return (0);
}
