/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:26:15 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/21 14:23:00 by msolinsk         ###   ########.fr       */
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

// 	RAYCASTER.C
int	init_ray(t_ray *ray, t_cub3d *cub3d, int x);
int	raycaster(t_cub3d *cub3d);


//	MAIN.C
void	ft_cprint(char *color, char *str);

//	FT_IMAGES.C
void	ft_print_img_info(t_sprite *img);
t_sprite	**ft_load_sprites(void *mlx);

//	FT_LOGS.C
void	ft_log(char *str, int level);

#endif
