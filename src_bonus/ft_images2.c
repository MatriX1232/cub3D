/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_images2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 15:09:37 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/04 15:17:25 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

void	ft_put_data(t_sprite *scaled, int nw, int nh, t_sprite *src)
{
	int		x;
	int		y;
	int		color;
	double	x_ratio;
	double	y_ratio;

	x_ratio = (double)src->width / nw;
	y_ratio = (double)src->height / nh;
	y = 0;
	while (y < nh)
	{
		x = 0;
		while (x < nw)
		{
			color = *(int *)(src->addr + ((int)(y * y_ratio) *\
			src->line_length + (int)(x * x_ratio) *(src->bits_per_pixel / 8)));
			*(int *)(scaled->addr + (y * scaled->line_length + x * \
				(scaled->bits_per_pixel / 8))) = color;
			x++;
		}
		y++;
	}
}

t_sprite	*ft_scale_sprite(t_cub3d *cub3d, t_sprite *src, int nw, int nh)
{
	t_sprite	*scaled;

	if (!src || nw <= 0 || nh <= 0)
		return (NULL);
	scaled = (t_sprite *) malloc(sizeof(t_sprite));
	if (!scaled)
		return (NULL);
	scaled->img = mlx_new_image(cub3d->mlx, nw, nh);
	if (!scaled->img)
		return (free(scaled), NULL);
	scaled->addr = mlx_get_data_addr(scaled->img, &scaled->bits_per_pixel, \
		&scaled->line_length, &scaled->endian);
	ft_put_data(scaled, nw, nh, src);
	scaled->width = nw;
	scaled->height = nh;
	scaled->path = src->path;
	ft_free_sprite(cub3d, src);
	return (scaled);
}
