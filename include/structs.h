/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:04:11 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/26 13:58:20 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs.h"

#ifndef STRUCTS_H
# define STRUCTS_H

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
	int	shift;
} t_keys;

typedef struct s_anim
{
	t_sprite	**sprites;
	int			frame;
	int			frame_count;
	int			frame_delay;
	int			duration;
}	t_anim;

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	move_speed;
} t_player;

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
	t_player	 *player;
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

} t_ray;


typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;
	t_sprite	**sprites;
	t_anim		**anims;
	t_sprite	*buffer;
	t_map		*map;
	t_player	*player;
	t_keys	keys;
	long		frame;
	short		delta_time;
	long		prev_time;
	int			gun_shooting;
	int			gun_frame;
	double	gun_anim_time;
}	t_cub3d;



#endif
