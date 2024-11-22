/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:04:11 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/21 14:14:36 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_map
{
	int		**map;
	int		w;
	int		h;
} t_map;

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
} t_player;

typedef struct s_cub3d
{
	void		*mlx;
	void		*win;
	int			w;
	int			h;

	t_map		map;
	t_player	player;
	t_sprite	**sprites;
}	t_cub3d;


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

#endif
