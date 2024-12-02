/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HUD.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:06:33 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/02 16:39:01 by msolinsk         ###   ########.fr       */
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
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->HUD->img, 0, WIN_HEIGHT - 1);
	ft_render_health(cub3d);
	ft_render_ammo(cub3d);
	ft_render_weapon(cub3d);
}

void	ft_render_weapon(t_cub3d *cub3d)
{
	t_weapon	*weapon;

	weapon = cub3d->player->current_weapon;
	// mlx_put_image_to_window(cub3d->mlx, cub3d->win, weapon->icon->img, 300, WIN_HEIGHT + 100);
	put_img_to_img(cub3d->buffer, weapon->icon, 300, WIN_HEIGHT + 100);
}

void	ft_render_health(t_cub3d *cub3d)
{
	// mlx_set_font(cub3d->mlx, cub3d->win, "Tiny5");
	if (!cub3d->player)
		return (ft_log("Player not found", NULL, 3));
	else if (cub3d->player)
	{
		if (cub3d->map->player->hp <= 35)
			draw_text(cub3d, "Tiny5", 40, "100", 510, WIN_HEIGHT + 80);
		else
			draw_text(cub3d, "Tiny5", 40, "100", 510, WIN_HEIGHT + 80);
	}
}

void	ft_render_ammo(t_cub3d *cub3d)
{
	char		*ammo_str;
	t_weapon	*weapon;

	weapon = cub3d->player->current_weapon;
	if (weapon->current_ammo == 0 && weapon->index != 1)
		draw_text(cub3d, "Tiny5", 40, "OUT", 640, WIN_HEIGHT + 80);
	else if (weapon->index > 1)
	{
		ammo_str = ft_itoa(weapon->current_ammo);
		if (ft_strlen(ammo_str) == 3)
			draw_text(cub3d, "Tiny5", 40, ammo_str, 660, WIN_HEIGHT + 80);
		else if (ft_strlen(ammo_str) == 2)
			draw_text(cub3d, "Tiny5", 40, ammo_str, 670, WIN_HEIGHT + 80);
		else if (ft_strlen(ammo_str) == 1)
			draw_text(cub3d, "Tiny5", 40, ammo_str, 680, WIN_HEIGHT + 80);
		free(ammo_str);
	}
	else
		draw_text(cub3d, "Tiny5", 20, "INFINITE", 650, WIN_HEIGHT + 80);
}
