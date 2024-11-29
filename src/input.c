
















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
}
