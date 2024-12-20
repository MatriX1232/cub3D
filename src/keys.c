/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:22:04 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/15 19:07:37 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	initialize_keys(t_cub3d *cub3d)
{
	cub3d->keys.w = 0;
	cub3d->keys.a = 0;
	cub3d->keys.s = 0;
	cub3d->keys.d = 0;
	cub3d->keys.left = 0;
	cub3d->keys.right = 0;
	cub3d->keys.shift = 0;
	cub3d->keys.mouse_1 = 0;
	cub3d->keys.up = 0;
	cub3d->keys.down = 0;
	cub3d->player->move_speed = MOVE_SPEED;
	cub3d->player->is_sprint = 0;
}
