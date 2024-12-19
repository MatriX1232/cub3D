/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_load4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:13:30 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/19 23:32:16 by msolinsk         ###   ########.fr       */
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

void	ft_handle_split(t_map *map, char **split, int *i, t_cub3d *cub3d)
{
	if (*i < 4)
		ft_load_texture(cub3d, map, split, *i);
	else if (*i < 6)
		ft_load_color(map, split, *i);
}
