/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:45:26 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/03 17:48:22 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

//	FOR ANIMATION	<BONUS>
#include <sys/time.h>

//	FOR READING TEXTURES FROM DIRECTORY	<BONUS>
#include <dirent.h>

int	ft_get_dir_count(char *path)
{
	DIR				*d;
	struct dirent	*dir;
	int				dir_count;

	dir_count = 0;
	d = opendir(path);
	if (!d)
		return (ft_log("Cannot open directory", path, 3), 0);
	dir = readdir(d);
	while (dir != NULL)
	{
		if (ft_strnstr(dir->d_name, ".xpm", ft_strlen(dir->d_name)))
			dir_count++;
		dir = readdir(d);
	}
	closedir(d);
	return (dir_count);
}

char	**ft_string_sort(char **names)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (names[i])
	{
		j = i + 1;
		while (names[j])
		{
			if (ft_strncmp(names[i], names[j], 10000) > 0)
			{
				tmp = names[i];
				names[i] = names[j];
				names[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return (names);
}

char	**ft_get_dir_files(char *path)
{
	DIR				*d;
	struct dirent	*dir;
	int				dir_len;
	char			**names;

	names = (char **)malloc((ft_get_dir_count(path) + 1) * sizeof(char *));
	if (!names)
		return (ft_log("Cannot allocate memory for names", NULL, 3), NULL);
	d = opendir(path);
	if (!d)
		return (ft_log("Cannot open directory", path, 3), NULL);
	dir_len = 0;
	dir = readdir(d);
	while (dir != NULL)
	{
		if (ft_strnstr(dir->d_name, ".xpm", ft_strlen(dir->d_name)))
			names[dir_len++] = ft_strdup(dir->d_name);
		dir = readdir(d);
	}
	names[dir_len] = NULL;
	closedir(d);
	names = ft_string_sort(names);
	if (ft_2d_len((void **)names) == 0)
		return (ft_log("No files in directory", path, 2), NULL);
	return (names);
}

t_sprite	**load_scale(t_cub3d *cub, char **names, t_sprite **imgs, char *dir)
{
	int		i;
	char	*tmp;

	i = 0;
	while (names[i])
	{
		tmp = ft_strjoin(dir, names[i]);
		imgs[i] = xpm_load_image(cub->mlx, tmp, 2);
		imgs[i] = ft_scale_sprite(cub, imgs[i], 300, 300);
		free(tmp);
		i++;
	}
	imgs[i] = NULL;
	ft_free_2d_array(names);
	return (imgs);
}

t_sprite	**load_batch(t_cub3d *cub3d, char *dir_path)
{
	char		**names;
	t_sprite	**sprites;
	int			len;

	names = ft_get_dir_files(dir_path);
	if (!names)
		return (ft_log("Cannot get directory files", NULL, 3), NULL);
	ft_log_sub("Loading sprites from directory...", dir_path, 1, 1);
	len = ft_2d_len((void **)names);
	sprites = (t_sprite **)malloc((len + 1) * sizeof(t_sprite *));
	if (!sprites)
		return (ft_log("Cannot allocate memory for sprites", NULL, 3), NULL);
	sprites = load_scale(cub3d, names, sprites, dir_path);
	return (sprites);
}
