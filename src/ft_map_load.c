/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:38:21 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/21 21:54:15 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_print_map(t_map *map)
{
	int i;

	i = 0;
	while (map->grid[i])
	{
		printf("%s\n", map->grid[i]);
		i++;
	}
}

static int	ft_get_map_height(char *path)
{
	int		fd;
	char	*line;
	int		height;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_log("Cannot open file", path, 3), 0);
	height = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		height++;
		free(line);
	}
	close(fd);
	return (height);
}

static void	ft_extract_info(t_map *map, char *line, int *i)
{
	char	**split;

	if (*i < 4)
		split = ft_split(line, ' ');
	if (*i == 0)
		map->pathNO = split[1];
	else if (*i == 1)
		map->pathSO = split[1];
	else if (*i == 2)
		map->pathWE = split[1];
	else if (*i == 3)
		map->pathEA = split[1];
	else
	{
		map->grid[*i - 4] = line;
		if ((int)ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
	}
	if (*i < 4)
		ft_free_2d_array(split);
	*i += 1;
}

t_map	*ft_load_map(char *path)
{
	t_map	*map;
	int		fd;
	char	*line;
	int		i;

	map = (t_map *)malloc(1 * sizeof(t_map));
	if (!map)
		return (ft_log("Cannot allocate memory for map", NULL, 3), NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_log("Cannot open file", path, 3), NULL);
	map->grid = (char **)malloc(ft_get_map_height(path) * sizeof(char *));
	if (!map)
		return (ft_log("Cannot allocate memory for map", NULL, 3), NULL);
	i = 0;
	while ((line = get_next_line(fd)) != NULL)
		ft_extract_info(map, line, &i);
	close(fd);
	ft_log("Map loaded sucessfully", path, 0);
	return (map);
}
