/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_images.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:48:53 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/21 19:15:03 by msolinsk         ###   ########.fr       */
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

t_sprite	*xpm_load_image(void *mlx, char *path)
{
	t_sprite	*ret;
	int			bpp;
	int			ll;
	int			ed;

	ret = (t_sprite *) malloc(1 * sizeof(t_sprite));
	if (!ret)
	{
		// printf("%s[ ERROR ] Cannot allocate memory for sprite: %s%s\n", RED, path, END);
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
	ft_log("Image loaded", path, 0);
	return (ret);
}

t_sprite	**ft_load_sprites(void *mlx)
{
	t_sprite	**sprites;

	sprites = (t_sprite **) malloc(9 * sizeof(t_sprite *));
	if (!sprites)
	{
		ft_log("Cannot allocate memory for sprites!", NULL, 3);
		return (NULL);
	}
	sprites[0] = xpm_load_image(mlx, "textures/blue_stone.xpm");
	sprites[1] = xpm_load_image(mlx, "textures/color_stone.xpm");
	sprites[2] = xpm_load_image(mlx, "textures/eagle.xpm");
	sprites[3] = xpm_load_image(mlx, "textures/grey_stone.xpm");
	sprites[4] = xpm_load_image(mlx, "textures/mossy.xpm");
	sprites[5] = xpm_load_image(mlx, "textures/purple_stone.xpm");
	sprites[6] = xpm_load_image(mlx, "textures/red_brick.xpm");
	sprites[7] = xpm_load_image(mlx, "textures/wood.xpm");
	sprites[8] = NULL;
	ft_log("All sprites loaded sucessfully!", NULL, 0);
	return (sprites);
}
