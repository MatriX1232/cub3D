/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:49:30 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/03 13:17:28 by msolinsk         ###   ########.fr       */
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
	if (sprite)
	{
		if (sprite->img)
			mlx_destroy_image(cub3d->mlx, sprite->img);
		free(sprite);
	}
}

void	ft_free_sprites(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	if (!cub3d->sprites)
		return ;
	while (cub3d->sprites[i])
		ft_free_sptite(cub3d, cub3d->sprites[i++]);
	if (cub3d->sprites)
		free(cub3d->sprites);
	if (cub3d->buffer)
		ft_free_sptite(cub3d, cub3d->buffer);
	ft_log("Sprites freed", NULL, 1);
}

void	ft_free_animations(t_cub3d *cub3d)
{
	int	i;
	int	j;

	i = 0;
	if (!cub3d->anims)
		return ;
	while (cub3d->anims[i])
	{
		j = 0;
		while (cub3d->anims[i]->sprites[j])
			ft_free_sptite(cub3d, cub3d->anims[i]->sprites[j++]);
		if (cub3d->anims[i]->sprites)
			free(cub3d->anims[i]->sprites);
		if (cub3d->anims[i])
			free(cub3d->anims[i]);
		i++;
	}
	if (cub3d->anims)
		free(cub3d->anims);
	ft_log("Animations freed", NULL, 1);
}

void	ft_free_font(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (cub3d->characters[i])
	{
		ft_free_sptite(cub3d, cub3d->characters[i]->sprite);
		free(cub3d->characters[i]);
		i++;
	}
}

void	ft_free_all(t_cub3d *cub3d)
{
	ft_free_font(cub3d);
	ft_free_animations(cub3d);
	ft_free_sptite(cub3d, cub3d->map->spriteNO);
	ft_free_sptite(cub3d, cub3d->map->spriteSO);
	ft_free_sptite(cub3d, cub3d->map->spriteWE);
	ft_free_sptite(cub3d, cub3d->map->spriteEA);
	ft_free_sprites(cub3d);
	ft_free_2d_array(cub3d->map->grid);
	ft_free_sptite(cub3d, cub3d->HUD);
	ft_free_sptite(cub3d, cub3d->weapons[1].icon);
	ft_free_sptite(cub3d, cub3d->weapons[2].icon);
	ft_free_sptite(cub3d, cub3d->weapons[3].icon);
	ft_free_sptite(cub3d, cub3d->weapons[4].icon);
	free(cub3d->map);
	free(cub3d->player); // Free player structure
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free(cub3d->mlx);
	exit(0);
}
