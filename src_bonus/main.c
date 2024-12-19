/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:32:15 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/20 00:00:35 by msolinsk         ###   ########.fr       */
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
	int		wp_index;

	frame_time = calculate_frame_time(cub3d);
	wp_index = cub3d->player->current_weapon->index - 1;
	handle_input(cub3d);
	update_doors(cub3d);
	raycaster(cub3d);
	if (cub3d->gun_shooting)
		update_animation(cub3d, cub3d->anims[wp_index]);
	draw_2_buffer(cub3d->buffer, \
		cub3d->anims[wp_index]->sprites[cub3d->anims[wp_index]->frame], \
		(int)((RENDER_WIDTH / 2) - 150), RENDER_HEIGHT - 300);
	ft_render_hud(cub3d, frame_time);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->buffer->img, 0, 0);
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->buffer_hud->img, 0, \
		RENDER_HEIGHT - 1);
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

	if (check_args(argc, argv))
		return (1);
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!mlx || !win)
		return (ft_log("Failed to initialize MLX or create window", \
			NULL, 3), 1);
	ft_log("MLX and WIN initialized", NULL, 1);
	ft_assign_mlx(&cub3d, mlx, win);
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
