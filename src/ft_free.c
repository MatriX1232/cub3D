/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 21:49:30 by msolinsk          #+#    #+#             */
/*   Updated: 2024/11/21 21:50:56 by msolinsk         ###   ########.fr       */
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

void	ft_free_all(t_cub3d *cub3d)
{
	ft_free_sprites(cub3d);
	ft_free_2d_array(cub3d->map->grid);
	free(cub3d->map->pathNO);
	free(cub3d->map->pathSO);
	free(cub3d->map->pathWE);
	free(cub3d->map->pathEA);
	free(cub3d->map);
	free(cub3d->player); // Free player structure
	mlx_destroy_window(cub3d->mlx, cub3d->win);
	mlx_destroy_display(cub3d->mlx);
	free(cub3d->mlx);
	exit(0);
}
