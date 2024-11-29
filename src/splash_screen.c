/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splash_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:40:37 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/30 00:00:05 by msolinsk         ###   ########.fr       */
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
	sleep(3);
	ft_free_sptite(cub3d, splash);
	return (0);
}

void	darken_image(t_sprite *sprite, int darken_value)
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

			// Extract RGB components
			unsigned char r = (color >> 16) & 0xFF;
			unsigned char g = (color >> 8) & 0xFF;
			unsigned char b = color & 0xFF;

			// Darken the RGB components
			r = (r > darken_value) ? r - darken_value : 0;
			g = (g > darken_value) ? g - darken_value : 0;
			b = (b > darken_value) ? b - darken_value : 0;

			// Combine the components back into a single color value
			color = (color & 0xFF000000) | (r << 16) | (g << 8) | b;
			*(unsigned int *)pixel = color;
		}
	}
}

void	lighten_image(t_sprite *sprite, int lighten_value)
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

			// Extract RGB components
			unsigned char r = (color >> 16) & 0xFF;
			unsigned char g = (color >> 8) & 0xFF;
			unsigned char b = color & 0xFF;

			// Darken the RGB components
			r = (r > lighten_value) ? r + lighten_value : 0;
			g = (g > lighten_value) ? g + lighten_value : 0;
			b = (b > lighten_value) ? b + lighten_value : 0;

			// Combine the components back into a single color value
			color = (color & 0xFF000000) | (r << 16) | (g << 8) | b;
			*(unsigned int *)pixel = color;
		}
	}
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
