/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_images.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:48:53 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/04 15:11:43 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/colors.h"
#include "../include/structs.h"
#include "../include/cub3d.h"

void	ft_print_img_info(t_sprite *img)
{
	if (img)
	{
		printf("Path: %s\n", img->path);
		printf("Bits_per_pixel: %d\n", img->bits_per_pixel);
		printf("Line_length: %d\n", img->line_length);
		printf("Width | Height: %d x %d\n", img->width, img->height);
		printf("Endian: %d\n\n", img->endian);
	}
}

t_sprite	*xpm_load_image(void *mlx, char *path, int sub_level)
{
	t_sprite	*ret;
	int			bpp;
	int			ll;
	int			ed;

	ret = (t_sprite *) malloc(1 * sizeof(t_sprite));
	if (!ret)
	{
		ft_log("Cannot allocate memory for sprite: ", path, 3);
		return (NULL);
	}
	bpp = 0;
	ll = 0;
	ed = 0;
	ret->img = mlx_xpm_file_to_image(mlx, path, &(ret->width), &(ret->height));
	if (ret->img == NULL)
		ft_log("Image failed to load", path, 3);
	ret->addr = mlx_get_data_addr(ret->img, &bpp, &ll, &ed);
	ret->path = path;
	ret->bits_per_pixel = bpp;
	ret->line_length = ll;
	ret->endian = ed;
	ft_log_sub("Image loaded", path, 0, sub_level);
	return (ret);
}

t_sprite	**ft_load_sprites(t_cub3d *cub3d)
{
	t_sprite	**sprites;

	sprites = (t_sprite **) malloc(10 * sizeof(t_sprite *));
	if (!sprites)
	{
		ft_log("Cannot allocate memory for sprites!", NULL, 3);
		return (NULL);
	}
	sprites[0] = xpm_load_image(cub3d->mlx, "textures/blue_stone.xpm", 1);
	sprites[1] = xpm_load_image(cub3d->mlx, "textures/color_stone.xpm", 1);
	sprites[2] = xpm_load_image(cub3d->mlx, "textures/grey_stone.xpm", 1);
	sprites[3] = xpm_load_image(cub3d->mlx, "textures/eagle.xpm", 1);
	sprites[4] = xpm_load_image(cub3d->mlx, "textures/mossy.xpm", 1);
	sprites[5] = xpm_load_image(cub3d->mlx, "textures/purple_stone.xpm", 1);
	sprites[6] = xpm_load_image(cub3d->mlx, "textures/red_brick.xpm", 1);
	sprites[7] = xpm_load_image(cub3d->mlx, "textures/wood.xpm", 1);
	sprites[8] = xpm_load_image(cub3d->mlx, "textures/door.xpm", 1);
	sprites[9] = NULL;
	ft_log("All sprites loaded sucessfully!", NULL, 0);
	return (sprites);
}
