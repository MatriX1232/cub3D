/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:22:14 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/19 22:36:43 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"
#include <sys/time.h>

unsigned long	rgb_to_hex(int r, int g, int b)
{
	return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff));
}

int	ft_2d_len(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

long	get_timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_assign_mlx(t_cub3d *cub3d, void *mlx, void *win)
{
	cub3d->mlx = mlx;
	cub3d->win = win;
	cub3d->win_width = WIN_WIDTH;
	cub3d->win_height = WIN_HEIGHT;
}

int	check_args(int argc, char **argv)
{
	int	len;

	len = (int)ft_strlen(argv[1]);
	if (argc == 1)
		return (ft_log("No arguments provided.", NULL, 2), 1);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".cub", len) != 0)
		return (ft_log("Invalid file extension. Expected '.cub'.", \
			NULL, 2), 1);
	else if (argc >= 3)
		return (ft_log("Too many arguments provided.", NULL, 2), 1);
	return (0);
}
