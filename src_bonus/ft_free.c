/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:49:30 by msolinsk          #+#    #+#             */
/*   Updated: 2025/01/30 17:50:20 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_free_sprite(t_cub3d *cub3d, t_sprite *sprite)
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
		ft_free_sprite(cub3d, cub3d->sprites[i++]);
	if (cub3d->sprites)
		free(cub3d->sprites);
	if (cub3d->buffer)
		ft_free_sprite(cub3d, cub3d->buffer);
	if (cub3d->buffer_hud)
		ft_free_sprite(cub3d, cub3d->buffer_hud);
	if (cub3d->hud)
		ft_free_sprite(cub3d, cub3d->hud);
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
			ft_free_sprite(cub3d, cub3d->anims[i]->sprites[j++]);
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

void	ft_free_all(t_cub3d *cub3d)
{
	if (cub3d->map)
	{
		if (cub3d->map->sprite_no)
			ft_free_sprite(cub3d, cub3d->map->sprite_no);
		if (cub3d->map->sprite_so)
			ft_free_sprite(cub3d, cub3d->map->sprite_so);
		if (cub3d->map->sprite_we)
			ft_free_sprite(cub3d, cub3d->map->sprite_we);
		if (cub3d->map->sprite_ea)
			ft_free_sprite(cub3d, cub3d->map->sprite_ea);
		if (cub3d->map->grid)
			ft_free_2d_array(cub3d->map->grid);
		free(cub3d->map);
	}
	ft_free_sprites(cub3d);
	if (cub3d->player)
		free(cub3d->player);
	ft_free_font(cub3d);
	ft_free_animations(cub3d);
	ft_free_weapons(cub3d);
	if (cub3d->win)
		mlx_destroy_window(cub3d->mlx, cub3d->win);
	if (cub3d->mlx)
	{
		mlx_destroy_display(cub3d->mlx);
		free(cub3d->mlx);
	}
	exit(0);
}