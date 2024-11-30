/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:28:34 by idomagal          #+#    #+#             */
/*   Updated: 2024/11/30 00:49:52 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void move_forward(t_cub3d *cub3d)
{
	double moveStepX = cub3d->player->dirx * cub3d->player->move_speed;
	double moveStepY = cub3d->player->diry * cub3d->player->move_speed;

	if (cub3d->map->grid[(int)(cub3d->player->posy)][(int)(cub3d->player->posx + moveStepX)] == '0')
		cub3d->player->posx += moveStepX;
	if (cub3d->map->grid[(int)(cub3d->player->posy + moveStepY)][(int)(cub3d->player->posx)] == '0')
		cub3d->player->posy += moveStepY;
}

void move_backward(t_cub3d *cub3d)
{
	double moveStepX = -cub3d->player->dirx * cub3d->player->move_speed;
	double moveStepY = -cub3d->player->diry * cub3d->player->move_speed;

	if (cub3d->map->grid[(int)(cub3d->player->posy)][(int)(cub3d->player->posx + moveStepX)] == '0')
		cub3d->player->posx += moveStepX;
	if (cub3d->map->grid[(int)(cub3d->player->posy + moveStepY)][(int)(cub3d->player->posx)] == '0')
		cub3d->player->posy += moveStepY;
}

void move_left(t_cub3d *cub3d)
{
	double moveStepX = -cub3d->player->planex * cub3d->player->move_speed;
	double moveStepY = -cub3d->player->planey * cub3d->player->move_speed;
	if (cub3d->map->grid[(int)(cub3d->player->posy)][(int)(cub3d->player->posx + moveStepX)] == '0')
		cub3d->player->posx += moveStepX;
	if (cub3d->map->grid[(int)(cub3d->player->posy + moveStepY)][(int)(cub3d->player->posx)] == '0')
		cub3d->player->posy += moveStepY;
}

void move_right(t_cub3d *cub3d)
{
	double moveStepX = cub3d->player->planex * cub3d->player->move_speed;
	double moveStepY = cub3d->player->planey * cub3d->player->move_speed;

	if (cub3d->map->grid[(int)(cub3d->player->posy)][(int)(cub3d->player->posx + moveStepX)] == '0')
		cub3d->player->posx += moveStepX;
	if (cub3d->map->grid[(int)(cub3d->player->posy + moveStepY)][(int)(cub3d->player->posx)] == '0')
		cub3d->player->posy += moveStepY;
}



void rotate_left(t_cub3d *cub3d)
{
	double oldDirX = cub3d->player->dirx;
	double oldPlaneX = cub3d->player->planex;
	double rotSpeed = ROT_SPEED;

	cub3d->player->dirx = cub3d->player->dirx * cos(-rotSpeed) - cub3d->player->diry * sin(-rotSpeed);
	cub3d->player->diry = oldDirX * sin(-rotSpeed) + cub3d->player->diry * cos(-rotSpeed);
	cub3d->player->planex = cub3d->player->planex * cos(-rotSpeed) - cub3d->player->planey * sin(-rotSpeed);
	cub3d->player->planey = oldPlaneX * sin(-rotSpeed) + cub3d->player->planey * cos(-rotSpeed);
}

void rotate_right(t_cub3d *cub3d)
{
	double oldDirX = cub3d->player->dirx;
	double oldPlaneX = cub3d->player->planex;
	double rotSpeed = ROT_SPEED;

	cub3d->player->dirx = cub3d->player->dirx * cos(rotSpeed) - cub3d->player->diry * sin(rotSpeed);
	cub3d->player->diry = oldDirX * sin(rotSpeed) + cub3d->player->diry * cos(rotSpeed);
	cub3d->player->planex = cub3d->player->planex * cos(rotSpeed) - cub3d->player->planey * sin(rotSpeed);
	cub3d->player->planey = oldPlaneX * sin(rotSpeed) + cub3d->player->planey * cos(rotSpeed);
}

void	look_up(t_cub3d *cub3d)
{
	double pitch_speed = 2.0;
	cub3d->player->pitch += pitch_speed;
	if (cub3d->player->pitch > (double)cub3d->win_height / 2)
		cub3d->player->pitch = (double)cub3d->win_height / 2;
}

void	look_down(t_cub3d *cub3d)
{
	double pitch_speed = 2.0;
	cub3d->player->pitch -= pitch_speed;
	if (cub3d->player->pitch < (double)-cub3d->win_height / 2)
		cub3d->player->pitch = (double)-cub3d->win_height / 2;
}

int ft_key_press(int keycode, t_cub3d *cub3d)
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
		cub3d->player->move_speed += 0.02;
	else if (keycode == XK_1)
		cub3d->player->current_weapon = &cub3d->weapons[1];
		cub3d->player->current_weapon = &cub3d->weapons[1];
	else if (keycode == XK_2)
		cub3d->player->current_weapon = &cub3d->weapons[2];
		cub3d->player->current_weapon = &cub3d->weapons[2];
	else if (keycode == XK_3)
		cub3d->player->current_weapon = &cub3d->weapons[3];
		cub3d->player->current_weapon = &cub3d->weapons[3];
	else if (keycode == XK_4)
		cub3d->player->current_weapon = &cub3d->weapons[4];
	else if (keycode == XK_Up)
		cub3d->keys.up = 1;
	else if (keycode == XK_Down)
		cub3d->keys.down = 1;
	return (0);
}

int ft_key_release(int keycode, t_cub3d *cub3d)
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
		cub3d->player->move_speed = MOVE_SPEED;
	else if (keycode == XK_Up)
		cub3d->keys.up = 0;
	else if (keycode == XK_Down)
		cub3d->keys.down = 0;
	return (0);
}

void handle_input(t_cub3d *cub3d)
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
