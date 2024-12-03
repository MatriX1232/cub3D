/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:39:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/03 16:51:11 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"
#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

t_font	**load_font(t_cub3d *cub3d, char *path, int font_size)
{
	t_font	**characters;
	t_font	*font;
	int		i;
	char	*new_path;
	char	c[2];

	characters = (t_font **)malloc(sizeof(t_font *) * 256);
	new_path = ft_calloc(256, sizeof(char));
	if (!characters)
		return (ft_log("Failed to allocate memory for font characters", NULL, 3), NULL);
	ft_log("Loading font characters", NULL, 1);
	i = 0;
	while (i < 256)
	{
		if (!(i >= '0' && i <= '9') && !(i >= 'A' && i <= 'Z'))
		{
			characters[i] = NULL;
			i++;
			continue;
		}
		c[0] = i;
		c[1] = '\0';
		ft_strlcat(new_path, path, 256);
		ft_strlcat(new_path, c, 256);
		ft_strlcat(new_path, ".xpm", 256);
		font = (t_font *)malloc(sizeof(t_font));
		if (!font)
			return (ft_log("Failed to allocate memory for font character", NULL, 3), NULL);
		font->sprite = xpm_load_image(cub3d->mlx, new_path, 1);
		if (font->sprite)
		{
			font->name = i;
			font->sprite = ft_scale_sprite(cub3d, font->sprite, (font_size * font->sprite->width) / font->sprite->height, font_size);
			characters[i] = font;
		}
		else
			ft_log("Failed to load font character", new_path, 2);
		new_path = ft_memset(new_path, 0, 256);
		i++;
	}
	free(new_path);
	return (characters);
}

void	draw_font(t_cub3d *cub3d, char *str, int x, int y, int offset)
{
	int		i;
	t_font	*font;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			x += offset;
			i++;
			continue;
		}
		font = cub3d->characters[(int)str[i]];
		if (font)
			draw_sprite_to_HUD(cub3d, font->sprite, x, y);
		else
			ft_log("Character not supported!", &str[i], 2);
		x += font->sprite->width + offset;
		i++;
	}
}
