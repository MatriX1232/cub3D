/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:44:12 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/20 15:47:34 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_set_default_state(t_cub3d *cub3d)
{
	initialize_keys(cub3d);
	cub3d->frame = 0;
	cub3d->prev_time = get_timestamp();
	cub3d->delta_time = 0;
	cub3d->gun_shooting = 0;
	cub3d->prev_shoot = 0;
}

int	ft_init_cub3d(t_cub3d *cub3d, char **argv)
{
	cub3d->map = ft_load_map(cub3d, argv[1]);
	if (!cub3d->map)
		return (ft_log("Map failed to load", NULL, 3), 1);
	cub3d->sprites = ft_load_sprites(cub3d);
	cub3d->hud = xpm_load_image(cub3d->mlx, "textures/hud.xpm", 0);
	if (!cub3d->sprites || !cub3d->hud)
		return (ft_log("Sprites failed to load", NULL, 3), 1);
	cub3d->buffer = ft_create_blank(cub3d, cub3d->win_width, cub3d->win_height);
	cub3d->buffer_hud = ft_create_blank(cub3d, \
		WIN_WIDTH, WIN_HEIGHT - RENDER_HEIGHT);
	if (!cub3d->buffer || !cub3d->buffer_hud)
		return (ft_log("Failed to create buffer", NULL, 3), 1);
	ft_replace_spaces(cub3d->map);
	if (ft_check_if_map_valid(cub3d->map))
		return (ft_log("Map is invalid", NULL, 3), 1);
	cub3d->player->current_weapon = &cub3d->weapons[1];
	cub3d->player->pitch = 100;
	cub3d->player->hp = 100;
	return (0);
}
