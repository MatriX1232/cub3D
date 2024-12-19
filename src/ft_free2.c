/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 11:44:19 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/19 21:56:53 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_free_map(t_map *map)
{
	if (map->grid)
		ft_free_2d_array(map->grid);
	if (map->sprite_no)
		free(map->sprite_no);
	if (map->sprite_so)
		free(map->sprite_so);
	if (map->sprite_we)
		free(map->sprite_we);
	if (map->sprite_ea)
		free(map->sprite_ea);
	free(map);
}

void	ft_free_font(t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 256)
	{
		if (cub3d->characters[i] != NULL)
			ft_free_sprite(cub3d, cub3d->characters[i]->sprite);
		free(cub3d->characters[i]);
		i++;
	}
	free(cub3d->characters);
}

void	ft_free_2d_array(char **array)
{
	int	i;

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
