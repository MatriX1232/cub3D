/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 14:40:25 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/04 14:42:27 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_key_weapon(int keycode, t_cub3d *cub3d)
{
	if (keycode == XK_1)
		cub3d->player->current_weapon = &cub3d->weapons[1];
	else if (keycode == XK_2)
		cub3d->player->current_weapon = &cub3d->weapons[2];
	else if (keycode == XK_3)
		cub3d->player->current_weapon = &cub3d->weapons[3];
	else if (keycode == XK_4)
		cub3d->player->current_weapon = &cub3d->weapons[4];
}

int	ft_key_press(int keycode, t_cub3d *cub3d)
{
	if (keycode == KEY_ESC)
		ft_exit(cub3d);
	else if (keycode == KEY_W)
		cub3d->keys.w = 1;
	else if (keycode == KEY_A)
		cub3d->keys.a = 1;
	else if (keycode == KEY_S)
		cub3d->keys.s = 1;
	else if (keycode == KEY_D)
		cub3d->keys.d = 1;
	else if (keycode == XK_Left)
		cub3d->keys.left = 1;
	else if (keycode == XK_Right)
		cub3d->keys.right = 1;
	else if (keycode == XK_Shift_L)
		cub3d->player->is_sprint = 1;
	else if (keycode == XK_Up)
		cub3d->keys.up = 1;
	else if (keycode == XK_Down)
		cub3d->keys.down = 1;
	else if (keycode == KEY_SPACE)
		try_open_door(cub3d);
	ft_key_weapon(keycode, cub3d);
	return (0);
}

int	ft_key_release(int keycode, t_cub3d *cub3d)
{
	if (keycode == KEY_W)
		cub3d->keys.w = 0;
	else if (keycode == KEY_A)
		cub3d->keys.a = 0;
	else if (keycode == KEY_S)
		cub3d->keys.s = 0;
	else if (keycode == KEY_D)
		cub3d->keys.d = 0;
	else if (keycode == XK_Left)
		cub3d->keys.left = 0;
	else if (keycode == XK_Right)
		cub3d->keys.right = 0;
	else if (keycode == XK_Shift_L)
		cub3d->player->is_sprint = 0;
	else if (keycode == XK_Up)
		cub3d->keys.up = 0;
	else if (keycode == XK_Down)
		cub3d->keys.down = 0;
	return (0);
}

void	handle_input(t_cub3d *cub3d)
{
	if (cub3d->keys.w)
		move_forward(cub3d);
	if (cub3d->keys.s)
		move_backward(cub3d);
	if (cub3d->keys.a)
		move_left(cub3d);
	if (cub3d->keys.d)
		move_right(cub3d);
	if (cub3d->keys.left)
		rotate_left(cub3d);
	if (cub3d->keys.right)
		rotate_right(cub3d);
	if (cub3d->keys.mouse_1)
		cub3d->gun_shooting = 1;
	if (cub3d->keys.up)
		look_up(cub3d);
	if (cub3d->keys.down)
		look_down(cub3d);
}
