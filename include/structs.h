/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:04:11 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/04 15:29:15 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"
#include <stdbool.h>

#ifndef STRUCTS_H
# define STRUCTS_H
# define MAX_DOORS 100

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_door
{
	int		x;
	int		y;
	int		open;
	long	open_time;
}	t_door;

typedef struct s_sprite
{
	void	*img;
	char	*addr;
	char	*path;
	int		bits_per_pixel;
	int		line_length;
	int		width;
	int		height;
	int		endian;
}	t_sprite;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
	int	up;
	int	down;
	int	shift;
	int	mouse_1;
}	t_keys;

typedef struct s_anim
{
	t_sprite	**sprites;
	int			frame;
	int			frame_count;
	int			frame_delay;
	long		last_update;
	bool		finished;
}	t_anim;

typedef struct s_font
{
	t_sprite	*sprite;
	char		name;
	int			size_x;
	int 		size_y;
}	t_font;

typedef struct s_weapon
{
	char		*name;
	t_sprite	*icon;
	int			index;
	int			current_ammo;
	int			ammo;
	int			reload_time;
	int			fire_rate;
}	t_weapon;

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	pitch;
	double	move_speed;
	t_weapon	*current_weapon;
	int		hp;
	int		max_hp;
}	t_player;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	t_sprite	*spriteNO;
	t_sprite	*spriteSO;
	t_sprite	*spriteWE;
	t_sprite	*spriteEA;
	int			floor;
	int			ceiling;
	t_player	*player;
}	t_map;


typedef struct s_ray
{
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int			mapx;
	int			mapy;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
}	t_ray;


typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	t_font		**characters;
	t_sprite	**sprites;
	t_sprite	*HUD;
	t_anim		**anims;
	t_sprite	*buffer;
	t_sprite	*buffer_HUD;
	t_map		*map;
	t_player	*player;
	t_keys		keys;
	t_weapon	weapons[5];
	long		frame;
	short		delta_time;
	long		prev_time;
	int			gun_shooting;
	long		prev_shoot;
	int			door_count;
	t_door	doors[MAX_DOORS];
}	t_cub3d;

#endif
