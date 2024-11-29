/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:01:42 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/29 00:32:12 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

//	FOR ANIMATION	<BONUS>
#include <sys/time.h>

//	FOR READING TEXTURES FROM DIRECTORY	<BONUS>
#include <dirent.h>

static int	ft_get_dir_count(char *path)
{
	DIR				*d;
	struct dirent	*dir;
	int				dir_count;

	dir_count = 0;
	d = opendir(path);
	if (!d)
		return (ft_log("Cannot open directory", path, 3), 0);
	while ((dir = readdir(d)) != NULL)
	{
		if (ft_strnstr(dir->d_name, ".xpm", ft_strlen(dir->d_name)))
			dir_count++;
	}
	closedir(d);
	return (dir_count);
}

static char	**ft_string_sort(char **names)
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

static char	**ft_get_dir_files(char *path)
{
	DIR				*d;
	struct dirent	*dir;
	int				dir_len;
	char			**names;

	dir_len = ft_get_dir_count(path);
	names = (char **)malloc((dir_len + 1) * sizeof(char *));
	if (!names)
		return (ft_log("Cannot allocate memory for names", NULL, 3), NULL);
	d = opendir(path);
	if (!d)
		return (ft_log("Cannot open directory", path, 3), NULL);
	dir_len = 0;
	while ((dir = readdir(d)) != NULL)
	{
		if (ft_strnstr(dir->d_name, ".xpm", ft_strlen(dir->d_name)))
			names[dir_len++] = ft_strdup(dir->d_name);
	}
	names[dir_len] = NULL;
	closedir(d);
	names = ft_string_sort(names);
	return (names);
}

t_sprite	**load_batch(t_cub3d *cub3d, char *dir_path)
{
	int			i;
	char		**names;
	t_sprite	**sprites;
	char		*tmp;

	ft_log_sub("Loading sprites from directory...", dir_path, 1, 1);
	names = ft_get_dir_files(dir_path);
	if (!names)
		return (ft_log("Cannot get directory files", NULL, 3), NULL);
	if (ft_2d_len((void **)names) == 0)
		return (ft_log("No files in directory", dir_path, 2), NULL);
	sprites = (t_sprite **)malloc((ft_2d_len((void **)names) + 1) * sizeof(t_sprite *));
	if (!sprites)
		return (ft_log("Cannot allocate memory for sprites", NULL, 3), NULL);
	i = 0;
	while (names[i])
	{
		tmp = ft_strjoin(dir_path, names[i]);
		sprites[i] = xpm_load_image(cub3d->mlx, tmp, 2);
		sprites[i] = ft_scale_sprite(cub3d, sprites[i], 300, 300);
		if (!sprites[i])
			return (ft_log("Cannot load image", names[i], 3), NULL);
		free(tmp);
		tmp = NULL;
		i++;
	}
	sprites[i] = NULL;
	ft_free_2d_array(names);
	return (sprites);
}

t_anim	*ft_load_anim(t_cub3d *cub3d, char *folder_path)
{
	t_anim	*anim;

	anim = (t_anim *)malloc(1 * sizeof(t_anim));
	if (!anim)
		return (ft_log("Cannot allocate memory for anim", NULL, 3), NULL);
	anim->frame = 0;
	anim->frame_count = ft_get_dir_count(folder_path);
	anim->frame_delay = (1000 / 60) * 1000;
	anim->duration = anim->frame_count * anim->frame_delay;
	anim->sprites = load_batch(cub3d, folder_path);
	if (!anim->sprites)
		return (ft_log("Cannot load batch", folder_path, 3), NULL);
	return (anim);
}

t_anim	**ft_laod_anims(t_cub3d *cub3d)
{
	t_anim	**anims;

	anims = (t_anim **)malloc(2 * sizeof(t_anim *));
	if (!anims)
		return (ft_log("Cannot allocate memory for anims", NULL, 3), NULL);
	ft_log("Loading animations...", NULL, 1);
	anims[0] = ft_load_anim(cub3d, "textures/pistol/");
	anims[1] = NULL;
	// anims[1] = ft_load_anim(cub3d, "textures/pistol/");
	// anims[2] = ft_load_anim(cub3d, "textures/long_rifle/");
	// anims[3] = ft_load_anim(cub3d, "textures/minigun/");/
	// anims[4] = NULL;
	return (anims);
}

void	ft_anim(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (cub3d->anims[i])
	{
		t_anim	*anim = cub3d->anims[i];
		while (anim->frame < anim->frame_count - 1)
		{
			mlx_put_image_to_window(cub3d->mlx, cub3d->win, anim->sprites[anim->frame]->img, WIN_WIDTH - 300, WIN_HEIGHT - 300);
			anim->frame++;
			usleep(anim->frame_delay * 20);
		}
		i++;
	}
}

void draw_sprite_to_buffer(t_cub3d *cub3d, t_sprite *sprite, int x_offset, int y_offset)
{
	int x, y;
	char *src_pixel;
	char *dst_pixel;
	int src_line_length = sprite->line_length;
	int dst_line_length = cub3d->buffer->line_length;
	int bytes_per_pixel = sprite->bits_per_pixel / 8;

	for (y = 0; y < sprite->height; y++)
	{
		if (y + y_offset < 0 || y + y_offset >= cub3d->win_height)
			continue;
		for (x = 0; x < sprite->width; x++)
		{
			if (x + x_offset < 0 || x + x_offset >= cub3d->win_width)
				continue;
			src_pixel = sprite->addr + y * src_line_length + x * bytes_per_pixel;
			dst_pixel = cub3d->buffer->addr + (y + y_offset) * dst_line_length + (x + x_offset) * bytes_per_pixel;
			unsigned int color = *(unsigned int *)src_pixel;
			if ((color & 0xFF000000) != 0xFF000000)
				*(unsigned int *)dst_pixel = color;
		}
	}
}

