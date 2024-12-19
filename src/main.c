/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:32:15 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/19 18:21:58 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

int	ft_exit(t_cub3d *cub3d)
{
	ft_free_all(cub3d);
	exit(0);
	return (0);
}

static double	calculate_frame_time(t_cub3d *cub3d)
{
	double	current_time;
	double	frame_time;
	double	min_frame_time;

	current_time = get_timestamp();
	frame_time = (current_time - cub3d->prev_time) / 1000.0;
	if (FRAME_RATE > 0)
	{
		min_frame_time = 1.0 / FRAME_RATE;
		if (frame_time < min_frame_time)
		{
			usleep((useconds_t)((min_frame_time - frame_time) * 1000000));
			current_time = get_timestamp();
			frame_time = (current_time - cub3d->prev_time) / 1000.0;
		}
	}
	cub3d->prev_time = current_time;
	cub3d->delta_time = frame_time;
	return (frame_time);
}

int	main_loop(t_cub3d *cub3d)
{
	double	frame_time;
	int		fps;
	char	*fps_str;

	frame_time = calculate_frame_time(cub3d);
	fps = (int)(1.0 / frame_time);
	if (fps < 0)
		fps = 0;
	fps_str = ft_itoa(fps);
	handle_input(cub3d);
	raycaster(cub3d);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->buffer->img, 0, 0);
	mlx_string_put(cub3d->mlx, cub3d->win, 0, 10, 0x00FF0000, "FPS:");
	mlx_string_put(cub3d->mlx, cub3d->win, 30, 10, 0x00FF0000, fps_str);
	free(fps_str);
	return (0);
}

static void	ft_handle_hooks(t_cub3d *cub3d)
{
	mlx_hook(cub3d->win, ON_DESTROY, 0, ft_exit, cub3d);
	mlx_hook(cub3d->win, ButtonPress, ButtonPressMask, mouse_press, cub3d);
	mlx_hook(cub3d->win, \
		ButtonRelease, \
		ButtonReleaseMask, \
		mouse_release, \
		cub3d);
	mlx_hook(cub3d->win, KeyPress, KeyPressMask, ft_key_press, cub3d);
	mlx_hook(cub3d->win, KeyRelease, KeyReleaseMask, ft_key_release, cub3d);
	mlx_hook(cub3d->win, MotionNotify, PointerMotionMask, mouse_move, cub3d);
}

int	main(int argc, char **argv)
{
	t_cub3d	cub3d;
	void	*mlx;
	void	*win;

	(void)argc;
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!mlx || !win)
		return (ft_log("Failed to initialize MLX or create window", \
			NULL, 3), 1);
	ft_log("MLX and WIN initialized", NULL, 1);
	cub3d.win_width = WIN_WIDTH;
	cub3d.win_height = WIN_HEIGHT;
	cub3d.mlx = mlx;
	cub3d.win = win;
	mlx_mouse_hide(cub3d.mlx, cub3d.win);
	if (ft_init_cub3d(&cub3d, argv) == 1)
		return (ft_exit(&cub3d), 1);
	if (ft_check_map_closed(cub3d.map))
		return (ft_exit(&cub3d), 1);
	ft_set_default_state(&cub3d);
	mlx_loop_hook(mlx, main_loop, &cub3d);
	ft_handle_hooks(&cub3d);
	mlx_loop(mlx);
	return (0);
}
