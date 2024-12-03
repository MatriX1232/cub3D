/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:39:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/03 13:31:31 by msolinsk         ###   ########.fr       */
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

	(void)font_size;
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
			i++;
			continue;
		}
		c[0] = i;
		c[1] = '\0';
		ft_strcat(new_path, path);
		ft_strcat(new_path, c);
		ft_strcat(new_path, ".xpm");
		font = (t_font *)malloc(sizeof(t_font));
		if (!font)
			return (ft_log("Failed to allocate memory for font character", NULL, 3), NULL);
		font->sprite = xpm_load_image(cub3d->mlx, new_path, 1);
		if (font->sprite)
		{
			font->name = i;
			font->sprite = ft_scale_sprite(cub3d, font->sprite, font_size, (font_size * font->sprite->height) / font->sprite->width);
			characters[i] = font;
		}
		else
			ft_log("Failed to load font character", new_path, 2);
		new_path = ft_memset(new_path, 0, 256);
		i++;
	}
	return (characters);
}

void	draw_font(t_cub3d *cub3d, char *str, int x, int y, int offset)
{
	int		i;
	t_font	*font;

	i = 0;
	while (str[i])
	{
		font = cub3d->characters[(int)str[i]];
		if (font)
		{
			mlx_put_image_to_window(cub3d->mlx, cub3d->win, font->sprite->img, x, y);
			// put_img_to_img(cub3d->buffer, font->sprite, x, y);
		}
		else
			ft_log("Character not supported!", NULL, 2);
		x += font->sprite->width + offset;
		i++;
	}
}

void	draw_text(t_cub3d *cub3d, const char *fontfile, int fontsize, const char *text, int x, int y)
{
	Display			*display = ((t_xvar *)cub3d->mlx)->display;
	Window 			window = ((t_win_list *)cub3d->win)->window;
	int 			screen = DefaultScreen(display);
	XftFont			*font;
	XftDraw			*draw;
	XftColor		color;
	XRenderColor	render_color = {0xffff, 0xffff, 0xffff, 0xffff}; // White color
	char 			fontname[256];

	// Create the font name with size
	snprintf(fontname, sizeof(fontname), "%s-%d", fontfile, fontsize);

	// Open the font
	font = XftFontOpenName(display, screen, fontname);
	if (!font)
		return (ft_log("Unable to open font", fontname, 3));

	// Create a drawable
	draw = XftDrawCreate(display, window, DefaultVisual(display, screen), DefaultColormap(display, screen));
	if (!draw)
		return (ft_log("Unable to create drawable", NULL, 3), XftFontClose(display, font));

	// Allocate color
	if (!XftColorAllocValue(display, DefaultVisual(display, screen), DefaultColormap(display, screen), &render_color, &color))
	{
		ft_log("Unable to allocate color", NULL, 3);
		return (XftDrawDestroy(draw), XftFontClose(display, font));
	}

	// Draw the text
	XftDrawStringUtf8(draw, &color, font, x, y, (XftChar8 *)text, strlen(text));

	// Clean up
	XftColorFree(display, DefaultVisual(display, screen), DefaultColormap(display, screen), &color);
	XftDrawDestroy(draw);
	XftFontClose(display, font);
}
