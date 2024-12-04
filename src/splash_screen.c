/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splash_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:40:37 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/04 11:59:17 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

int	splash_screen(t_cub3d *cub3d)
{
	t_sprite	*splash;

	splash = xpm_load_image(cub3d->mlx, "textures/splash_screen.xpm", 0);
	if (!splash)
		return (ft_log("Cannot load splash screen", NULL, 3), -1);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, splash->img, 0, 0);
	sleep(1);
	ft_free_sptite(cub3d, splash);
	return (0);
}
