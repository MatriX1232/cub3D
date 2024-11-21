/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:26:15 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/21 22:15:57 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <mlx_int.h>
# include "structs.h"
# include <stdio.h>

# define KEY_ESC 65307
# define ON_DESTROY 17

//	MAIN.C
void	ft_cprint(char *color, char *str);

//	FT_IMAGES.C
void	ft_print_img_info(t_sprite *img);
t_sprite	**ft_load_sprites(void *mlx);
t_sprite	*xpm_load_image(void *mlx, char *path);
void	ft_free_sprites(t_cub3d *cub3d);

//	FT_DRAW.C
void put_img_to_img(t_sprite *dest_img, t_sprite *src_img, int dest_x, int dest_y);

//	FT_LOGS.C
void	ft_log(char *str, char *str_optional, int level);

//	FT_MAP.C
t_map	*ft_load_map(char *path);

//	GNL.C
char	*get_next_line(int fd);

//	UTILS.C
unsigned long	rgb_to_hex(int r, int g, int b);

//	FT_FREE.C
void	ft_free_2d_array(char **array);

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
} t_player;

typedef struct s_ray
{
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
