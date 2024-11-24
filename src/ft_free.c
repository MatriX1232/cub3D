/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:49:30 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/24 17:20:14 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_free_2d_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}

void	ft_free_sptite(t_cub3d *cub3d, t_sprite *sprite)
{
	mlx_destroy_image(cub3d->mlx, sprite->img);
	free(sprite);
}

void	ft_free_sprites(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (cub3d->sprites[i])
		ft_free_sptite(cub3d, cub3d->sprites[i++]);
	free(cub3d->sprites);
	ft_free_sptite(cub3d, cub3d->buffer);
	ft_log("Sprites freed", NULL, 1);
}

void	ft_free_all(t_cub3d *cub3d)
{
	ft_free_sptite(cub3d, cub3d->map->spriteNO);
	ft_free_sptite(cub3d, cub3d->map->spriteSO);
	ft_free_sptite(cub3d, cub3d->map->spriteWE);
	ft_free_sptite(cub3d, cub3d->map->spriteEA);
	ft_free_sprites(cub3d);
	ft_free_2d_array(cub3d->map->grid);
	free(cub3d->map);
	free(cub3d->player); // Free player structure
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free(cub3d->mlx);
	exit(0);
}
