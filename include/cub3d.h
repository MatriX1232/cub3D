/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:26:15 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/22 18:03:43 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <mlx_int.h>
# include "structs.h"
# include <stdio.h>
#	include <math.h>

# define KEY_ESC 65307
# define ON_DESTROY 17
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

// 	RAYCASTER.C
int	init_ray(t_ray *ray, t_cub3d *cub3d, int x);
int	raycaster(t_cub3d *cub3d);

//	MAIN.C
void	ft_cprint(char *color, char *str);

//	FT_IMAGES.C
void	ft_print_img_info(t_sprite *img);
t_sprite	**ft_load_sprites(t_cub3d *cub3d);
t_sprite	*xpm_load_image(void *mlx, char *path);
void	ft_free_sprites(t_cub3d *cub3d);

//	ANIM.C
void	ft_anim(t_cub3d *cub3d);

//	FT_DRAW.C
void put_img_to_img(t_sprite *dest_img, t_sprite *src_img, int dest_x, int dest_y);
void put_pixel_to_img(t_sprite *img, int x, int y, int color);

//	FT_MINIMAP.C
void	ft_draw_minimap(t_cub3d *cub3d, int px, int py);

//	FT_LOGS.C
void	ft_log(char *str, char *str_optional, int level);
void	ft_log_sub(char *str, char *str_optional, int level, int sub_level);

//	FT_MAP.C
t_map	*ft_load_map(char *path);

//	GNL.C
char	*get_next_line(int fd);

//	UTILS.C
unsigned long	rgb_to_hex(int r, int g, int b);
int				ft_2d_len(void **array);

//	FT_FREE.C
void	ft_free_2d_array(char **array);

#endif
