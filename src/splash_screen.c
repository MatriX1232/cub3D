/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splash_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:40:37 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/03 13:13:52 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

int	splash_screen(t_cub3d *cub3d)
{
	t_sprite	*splash;

	splash = xpm_load_image(cub3d->mlx, "textures/splash_screen.xpm", 0);
	if (!splash)
		return (ft_log("Cannot load splash screen", NULL, 3), -1);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, splash->img, 0, 0);
	sleep(1);
	ft_free_sptite(cub3d, splash);
	return (0);
}

void change_sprite_transparency(t_sprite *sprite, unsigned char transparency)
{
	int x, y;
	int bytes_per_pixel = sprite->bits_per_pixel / 8;
	char *pixel;

	for (y = 0; y < sprite->height; y++)
	{
		for (x = 0; x < sprite->width; x++)
		{
			pixel = sprite->addr + (y * sprite->line_length + x * bytes_per_pixel);
			unsigned int color = *(unsigned int *)pixel;
			// Modify the alpha channel
			color = (color & 0x00FFFFFF) | (transparency << 24);
			*(unsigned int *)pixel = color;
		}
	}
}
