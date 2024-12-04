/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:39:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/04 11:49:08 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"
#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

int	fit_height(int size, t_sprite *sprite)
{
	return ((size * sprite->width / sprite->height));
}

t_font	*load_char(t_cub3d *cub3d, char *path, char c[2], int font_size)
{
	t_font	*font;
	char	*new_path;
	int		wid;

	font = (t_font *)malloc(sizeof(t_font));
	if (!font)
		return (ft_log("Failed to allocate font mem", NULL, 3), NULL);
	new_path = ft_calloc(256, sizeof(char));
	ft_strlcat(new_path, path, 256);
	ft_strlcat(new_path, c, 256);
	ft_strlcat(new_path, ".xpm", 256);
	font->sprite = xpm_load_image(cub3d->mlx, new_path, 1);
	if (font->sprite)
	{
		font->name = c[0];
		wid = fit_height(font_size, font->sprite);
		font->sprite = ft_scale_sprite(cub3d, font->sprite, wid, font_size);
	}
	else
		ft_log("Failed to load font character", new_path, 2);
	free(new_path);
	return (font);
}

t_font	**load_font(t_cub3d *cub3d, char *path, int font_size)
{
	t_font	**characters;
	int		i;
	char	c[2];

	characters = (t_font **)malloc(sizeof(t_font *) * 256);
	if (!characters)
		return (ft_log("Failed to allocate memory for font", NULL, 3), NULL);
	ft_log("Loading font characters", NULL, 1);
	i = 0;
	while (i < 256)
	{
		if (!(i >= '0' && i <= '9') && !(i >= 'A' && i <= 'Z'))
		{
			characters[i] = NULL;
			i++;
			continue ;
		}
		c[0] = i;
		c[1] = '\0';
		characters[i] = load_char(cub3d, path, c, font_size);
		i++;
	}
	return (characters);
}

void	draw_font(t_cub3d *cub3d, char *str, int x, int y)
{
	int		i;
	t_font	*font;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			x += OFFSET;
			i++;
			continue ;
		}
		font = cub3d->characters[(int)str[i]];
		if (font)
			draw_2_buffer(cub3d->HUD, font->sprite, x, y);
		else
			ft_log("Character not supported!", &str[i], 2);
		x += font->sprite->width + OFFSET;
		i++;
	}
}
