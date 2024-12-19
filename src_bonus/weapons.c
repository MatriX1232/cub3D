/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:41:55 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/04 12:09:13 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_change_icon_size(t_cub3d *cub3d)
{
	int			i;
	t_sprite	*tmp;

	i = 1;
	while (i < 5 && cub3d->weapons[i].name != NULL)
	{
		tmp = cub3d->weapons[i].icon;
		tmp = ft_scale_sprite(cub3d, tmp, 200, 85);
		cub3d->weapons[i].icon = tmp;
		i++;
	}
}

void	init_weapons(t_cub3d *cub3d)
{
	char		*pistol;
	char		*rifle;
	char		*minigun;

	pistol = ft_strdup("textures/Pistol_icon.xpm");
	rifle = ft_strdup("textures/Longrifle_icon.xpm");
	minigun = ft_strdup("textures/Minigun_icon.xpm");
	cub3d->weapons[1] = (t_weapon){"KNIFE", NULL, 1, 0, 0, 0, 5000};
	cub3d->weapons[1].icon = xpm_load_image(cub3d->mlx, pistol, 0);
	cub3d->weapons[2] = (t_weapon){"PISTOL", NULL, 2, 15, 15, 0, 1000};
	cub3d->weapons[2].icon = xpm_load_image(cub3d->mlx, pistol, 0);
	cub3d->weapons[3] = (t_weapon){"LONG RIFLE", NULL, 3, 50, 50, 0, 300};
	cub3d->weapons[3].icon = xpm_load_image(cub3d->mlx, rifle, 0);
	cub3d->weapons[4] = (t_weapon){"MINIGUN", NULL, 4, 500, 500, 0, 50};
	cub3d->weapons[4].icon = xpm_load_image(cub3d->mlx, minigun, 0);
	ft_change_icon_size(cub3d);
	free(pistol);
	free(rifle);
	free(minigun);
}
