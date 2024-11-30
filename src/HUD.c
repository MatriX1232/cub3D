/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HUD.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:06:33 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/30 01:19:36 by msolinsk         ###   ########.fr       */
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


void	ft_render_health(t_cub3d *cub3d)
{
	// mlx_set_font(cub3d->mlx, cub3d->win, "Tiny5");
	if (!cub3d->player)
		return (ft_log("Player not found", NULL, 3));
	else if (cub3d->player)
	{
		if (cub3d->map->player->hp <= 35)
			mlx_string_put(cub3d->mlx, cub3d->win, 10, 30, 0xFF0000, "HEALTH: 100");
		else
			mlx_string_put(cub3d->mlx, cub3d->win, 10, 30, 0xFFFFFF, "HEALTH: 100");
	}
}

void	ft_render_ammo(t_cub3d *cub3d)
{
	char	*ammo_str;
	t_weapon	*weapon;

	weapon = cub3d->player->current_weapon;
	// mlx_set_font(cub3d->mlx, cub3d->win, "-*-helvetica-*-r-*-*-24-*-*-*-*-*-*-*");
	mlx_string_put(cub3d->mlx, cub3d->win, 10, 40, 0xFFFFFF, weapon->name);
	if (weapon->current_ammo == 0 && weapon->index != 1)
		mlx_string_put(cub3d->mlx, cub3d->win, 10, 50, 0xFF0000, "AMMO: OUT OF AMMO");
	else if (weapon->index > 1)
	{
		ammo_str = ft_itoa(weapon->current_ammo);
		mlx_string_put(cub3d->mlx, cub3d->win, 10, 50, 0xFFFFFF, "AMMO: ");
		mlx_string_put(cub3d->mlx, cub3d->win, 60, 50, 0xFFFFFF, ammo_str);
		free(ammo_str);
	}
	else
		mlx_string_put(cub3d->mlx, cub3d->win, 10, 50, 0xFFFFFF, "AMMO: INFINITE");
}
