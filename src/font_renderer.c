/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   font_renderer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 21:39:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/02 15:59:18 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

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

void	font_test(t_cub3d *cub3d)
{
	long	start;

	start = get_timestamp();
	while (get_timestamp() - start < 2000)
	{
		draw_text(cub3d, "Tiny5", 20, "Hello, world!", 150, 150);
	}
}
