/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:38:21 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/17 18:22:30 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

static char	**ft_handle_split_sep(char **split, char *line, int *i)
{
	if (*i < 6)
	{
		if (*i < 4)
			split = ft_split(line, ' ');
		else
			split = ft_split(line, ',');
	}
	return (split);
}

static void	ft_extract_info(t_cub3d *cub3d, t_map *map, char *line, int *i)
{
	char		**split;
	char		*tmp;

	tmp = ft_strtrim(line, "\n");
	free(line);
	line = tmp;
	if (ft_strlen(line) == 0)
	{
		free(line);
		return ;
	}
	split = NULL;
	split = ft_handle_split_sep(split, line, i);
	if (*i < 6)
		ft_handle_split(map, split, i, cub3d);
	else
		ft_process_grid(cub3d, map, line, *i - 6);
	if (*i < 6)
		ft_free_2d_array(split);
	free(line);
	*i += 1;
}

static t_map	*ft_init_map(t_map *map)
{
	map = (t_map *) malloc(1 * sizeof(t_map));
	if (!map)
		return (ft_log("Cannot allocate memory for map", NULL, 3), NULL);
	map->player = (t_player *) malloc(1 * sizeof(t_player));
	if (!map->player)
		return (ft_log("Cannot allocate memory for player", NULL, 3), NULL);
	return (map);
}

static t_map	*ft_init_grid(t_map *map, char *path)
{
	int	j;

	map->height = ft_get_map_height(path) - 6;
	if (map->height < 0 || \
		(unsigned long)map->height > (9223372036854775807 / sizeof(char *) - 1))
		return (ft_log("Invalid map height", NULL, 3), NULL);
	map->grid = (char **)malloc((map->height + 1) * sizeof(char *));
	if (!map->grid)
		return (ft_log("Cannot allocate memory for map grid", NULL, 3), NULL);
	j = 0;
	while (j < map->height)
		map->grid[j++] = NULL;
	return (map);
}

t_map	*ft_load_map(t_cub3d *cub3d, char *path)
{
	t_map	*map;
	int		fd;
	char	*line;
	int		i;

	map = NULL;
	map = ft_init_map(map);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_log("Cannot open file", path, 3), NULL);
	map = ft_init_grid(map, path);
	i = 0;
	map->width = 0;
	cub3d->player = map->player;
	ft_log("Loading map textures...", NULL, 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		ft_extract_info(cub3d, map, line, &i);
		line = get_next_line(fd);
	}
	map->grid[i - 6] = NULL;
	close(fd);
	ft_log("Map loaded successfully", path, 0);
	return (map);
}
