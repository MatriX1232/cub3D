/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:17:01 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/18 17:34:51 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBS_H
# define LIBS_H

# define RENDER_WIDTH 800
# define RENDER_HEIGHT 600
# define WIN_WIDTH 800
# define WIN_HEIGHT 701

# define MINIMAP_SCALE 7
# define MINIMAP_FG 0x3b014a
# define MINIMAP_BG 0xd9fff2

# include "../include/colors.h"
# include "../include/cub3d.h"
# include "../include/libft.h"
# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include "../include/structs.h"
# include <X11/X.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#endif
