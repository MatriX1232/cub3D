/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HUD.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:06:33 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/17 18:59:17 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

/*
# Create the user-specific fonts directory if it doesn't exist
mkdir -p ~/.local/share/fonts

# Copy the font file to the user-specific fonts directory
cp Tiny5.ttf ~/.local/share/fonts/

# Update the font cache
fc-cache -fv

# Verify the font installation
fc-list | grep "Tiny5"
*/

void	ft_render_hud(t_cub3d *cub3d, int frame_time)
{
	draw_2_buffer(cub3d->buffer_hud, cub3d->hud, 0, 0);
	ft_render_health(cub3d);
	ft_render_ammo(cub3d);
	ft_render_weapon(cub3d);
	ft_render_framerate(cub3d, frame_time);
	(void)frame_time;
}

void	ft_render_framerate(t_cub3d *cub3d, int frame_time)
{
	int		fps;
	char	*fps_str;

	fps = (int)(1.0 / frame_time);
	if (fps < 0)
		fps = 0;
	fps_str = ft_itoa(fps);
	draw_font(cub3d, "FPS", 130, 50);
	draw_font(cub3d, fps_str, 220, 50);
	free(fps_str);
}

void	ft_render_weapon(t_cub3d *cub3d)
{
	t_weapon	*weapon;

	weapon = cub3d->player->current_weapon;
	draw_2_buffer(cub3d->buffer_hud, weapon->icon, 345, 5);
}

void	ft_render_health(t_cub3d *cub3d)
{
	if (!cub3d->player)
		return (ft_log("Player not found", NULL, 3));
	else if (cub3d->player)
	{
		if (cub3d->map->player->hp <= 35)
			draw_font(cub3d, "35", 510, 45);
		else
			draw_font(cub3d, "100", 510, 45);
	}
}

void	ft_render_ammo(t_cub3d *cub3d)
{
	char		*ammo_str;
	t_weapon	*weapon;

	weapon = cub3d->player->current_weapon;
	if (weapon->current_ammo == 0 && weapon->index != 1)
		draw_font(cub3d, "OUT", 665, 45);
	else if (weapon->index > 1)
	{
		ammo_str = ft_itoa(weapon->current_ammo);
		if (ft_strlen(ammo_str) == 3)
			draw_font(cub3d, ammo_str, 665, 45);
		else if (ft_strlen(ammo_str) == 2)
			draw_font(cub3d, ammo_str, 665, 45);
		else if (ft_strlen(ammo_str) == 1)
			draw_font(cub3d, ammo_str, 665, 45);
		free(ammo_str);
	}
	else
		draw_font(cub3d, "INF", 665, 45);
}
