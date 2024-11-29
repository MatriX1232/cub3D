/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map_load.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:38:21 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/29 23:35:21 by msolinsk         ###   ########.fr       */
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

static void	ft_extract_info(t_cub3d *cub3d, t_map *map, char *line, int *i)
{
	t_player	*player;
	char		**split;
	char		*tmp;

	player = cub3d->player;
	tmp = ft_strtrim(line, "\n");
	free(line);
	line = tmp;

	// Skip empty lines
	if (ft_strlen(line) == 0)
		return (free(line));

	if (*i < 4)
		split = ft_split(line, ' ');
	if (*i == 4 || *i == 5)
		split = ft_split(line + 1, ',');
	if (*i == 0)
		map->spriteNO = xpm_load_image(cub3d->mlx, split[1], 1);
	else if (*i == 1)
		map->spriteSO = xpm_load_image(cub3d->mlx, split[1], 1);
	else if (*i == 2)
		map->spriteWE = xpm_load_image(cub3d->mlx, split[1], 0);
	else if (*i == 3)
		map->spriteEA = xpm_load_image(cub3d->mlx, split[1], 0);
	else if (*i == 4)
		map->floor = (int)rgb_to_hex(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
	else if (*i == 5)
		map->ceiling = (int)rgb_to_hex(ft_atoi(split[0]), ft_atoi(split[1]), ft_atoi(split[2]));
	else
	{
		map->grid[*i - 6] = ft_strdup(line);
		if (!map->grid[*i - 6])
			ft_log("Cannot allocate memory for map grid", NULL, 3);
		int y = *i - 6;
		for (int x = 0; line[x]; x++)
		{
			if (line[x] == 'N' || line[x] == 'S' || line[x] == 'E' || line[x] == 'W')
			{
				player->posx = x + 0.5;
				player->posy = y + 0.5;
				if (line[x] == 'N')
				{
					player->dirx = 0;
					player->diry = -1;
					player->planex = 0.66;
					player->planey = 0;
				}
				else if (line[x] == 'S')
				{
					player->dirx = 0;
					player->diry = 1;
					player->planex = -0.66;
					player->planey = 0;
				}
				else if (line[x] == 'E')
				{
					player->dirx = 1;
					player->diry = 0;
					player->planex = 0;
					player->planey = 0.66;
				}
				else if (line[x] == 'W')
				{
					player->dirx = -1;
					player->diry = 0;
					player->planex = 0;
					player->planey = -0.66;
				}
				map->grid[y][x] = '0';
			}
		}
		if ((int)ft_strlen(line) > map->width)
			map->width = ft_strlen(line);
	}
	if (*i < 6)
		ft_free_2d_array(split);
	free(line);
	*i += 1;
}

t_map	*ft_load_map(t_cub3d *cub3d, char *path)
{
	t_map	*map;
	int		fd;
	char	*line;
	int		i;

	map = (t_map *)malloc(1 * sizeof(t_map));
	if (!map)
		return (ft_log("Cannot allocate memory for map", NULL, 3), NULL);
	map->player = (t_player *) malloc(1 * sizeof(t_player));
	if (!map->player)
		return (ft_log("Cannot allocate memory for player", NULL, 3), NULL);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (ft_log("Cannot open file", path, 3), NULL);
	map->height = ft_get_map_height(path) - 6;
	map->grid = (char **)malloc((map->height + 1) * sizeof(char *));
	if (!map->grid)
		return (ft_log("Cannot allocate memory for map grid", NULL, 3), NULL);
	for (int j = 0; j < map->height; j++)
		map->grid[j] = NULL;
	i = 0;
	map->width = 0;
	cub3d->player = map->player;
	ft_log("Loading map textures...", NULL, 1);
	while ((line = get_next_line(fd)) != NULL)
		ft_extract_info(cub3d, map, line, &i);
	map->grid[i - 6] = NULL;
	close(fd);
	ft_log("Map loaded successfully", path, 0);
	return (map);
}
