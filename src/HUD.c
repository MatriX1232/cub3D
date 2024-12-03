/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HUD.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:06:33 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/03 17:08:47 by msolinsk         ###   ########.fr       */
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

void	ft_render_HUD(t_cub3d *cub3d)
{
	draw_sprite_to_HUD(cub3d, cub3d->HUD, 0, 0);
	ft_render_health(cub3d);
	ft_render_ammo(cub3d);
	ft_render_weapon(cub3d);
}

void	ft_render_weapon(t_cub3d *cub3d)
{
	t_weapon	*weapon;

	weapon = cub3d->player->current_weapon;
	draw_sprite_to_HUD(cub3d, weapon->icon, 345, 5);
}

void	ft_render_health(t_cub3d *cub3d)
{
	if (!cub3d->player)
		return (ft_log("Player not found", NULL, 3));
	else if (cub3d->player)
	{
		if (cub3d->map->player->hp <= 35)
			draw_font(cub3d, "35", 510, 45, 5);
		else
			draw_font(cub3d, "100", 510, 45, 5);
	}
}

void	ft_render_ammo(t_cub3d *cub3d)
{
	char		*ammo_str;
	t_weapon	*weapon;

	weapon = cub3d->player->current_weapon;
	if (weapon->current_ammo == 0 && weapon->index != 1)
		draw_font(cub3d, "OUT", 665, 45, 5);
	else if (weapon->index > 1)
	{
		ammo_str = ft_itoa(weapon->current_ammo);
		if (ft_strlen(ammo_str) == 3)
			draw_font(cub3d, ammo_str, 665, 45, 5);
		else if (ft_strlen(ammo_str) == 2)
			draw_font(cub3d, ammo_str, 665, 45, 5);
		else if (ft_strlen(ammo_str) == 1)
			draw_font(cub3d, ammo_str, 665, 45, 5);
		free(ammo_str);
	}
	else
		draw_font(cub3d, "INF", 665, 45, 5);
}
