/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HUD.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 00:06:33 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/30 00:51:42 by msolinsk         ###   ########.fr       */
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
	if (cub3d->player->hp <= 35)
		mlx_string_put(cub3d->mlx, cub3d->win, 10, 40, 0xFF0000, "HEALTH: 100");
	else
		mlx_string_put(cub3d->mlx, cub3d->win, 10, 40, 0xFFFFFF, "HEALTH: 100");
}

void	ft_render_ammo(t_cub3d *cub3d)
{
	char	*ammo_str;
	// mlx_set_font(cub3d->mlx, cub3d->win, "-*-helvetica-*-r-*-*-24-*-*-*-*-*-*-*");
	if (cub3d->ammo == 0)
		mlx_string_put(cub3d->mlx, cub3d->win, 10, 50, 0xFF0000, "AMMO: OUT OF AMMO");
	else if (cub3d->weapon_idx > 0)
	{
		ammo_str = ft_itoa(cub3d->ammo);
		mlx_string_put(cub3d->mlx, cub3d->win, 10, 50, 0xFFFFFF, "AMMO: ");
		mlx_string_put(cub3d->mlx, cub3d->win, 60, 50, 0xFFFFFF, ammo_str);
		free(ammo_str);
	}
	else
		mlx_string_put(cub3d->mlx, cub3d->win, 10, 50, 0xFFFFFF, "AMMO: INFINITE");
}
