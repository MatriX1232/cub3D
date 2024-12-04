/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:01:42 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/04 15:19:26 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/libs.h"

//	FOR ANIMATION	<BONUS>
#include <sys/time.h>

//	FOR READING TEXTURES FROM DIRECTORY	<BONUS>
#include <dirent.h>

t_anim	*ft_load_anim(t_cub3d *cub3d, char *folder_path)
{
	t_anim	*anim;

	anim = (t_anim *) malloc(1 * sizeof(t_anim));
	if (!anim)
		return (ft_log("Cannot allocate memory for anim", NULL, 3), NULL);
	anim->frame = 0;
	anim->frame_count = ft_get_dir_count(folder_path);
	anim->frame_delay = 70;
	anim->sprites = load_batch(cub3d, folder_path);
	anim->finished = true;
	anim->last_update = 0;
	if (!anim->sprites)
		return (ft_log("Cannot load batch", folder_path, 3), NULL);
	return (anim);
}

t_anim	**ft_load_anims(t_cub3d *cub3d)
{
	t_anim	**anims;

	anims = (t_anim **)malloc(5 * sizeof(t_anim *));
	if (!anims)
		return (ft_log("Cannot allocate memory for anims", NULL, 3), NULL);
	ft_log("Loading animations...", NULL, 1);
	anims[0] = ft_load_anim(cub3d, "textures/knife/");
	anims[1] = ft_load_anim(cub3d, "textures/pistol/");
	anims[2] = ft_load_anim(cub3d, "textures/long_rifle/");
	anims[3] = ft_load_anim(cub3d, "textures/minigun/");
	anims[4] = NULL;
	init_weapons(cub3d);
	return (anims);
}

void	finish_shooting(t_cub3d *cub3d, t_anim *anim)
{
	int	x;
	int	y;

	x = (int)((WIN_WIDTH / 2) - 150);
	y = WIN_HEIGHT - 300;
	anim->frame = 0;
	anim->finished = true;
	cub3d->gun_shooting = false;
	draw_2_buffer(cub3d->buffer, anim->sprites[anim->frame], x, y);
}

void	change_frame(t_cub3d *cub3d, t_anim *anim, long current_time)
{
	if (anim->frame == anim->frame_count - 1)
	{
		cub3d->gun_shooting = false;
		anim->finished = true;
		anim->frame = 0;
	}
	else
	{
		anim->frame = (anim->frame + 1) % anim->frame_count;
		anim->last_update = current_time;
	}
}

int	update_animation(t_cub3d *cub3d, t_anim *anim)
{
	long			current_time;
	long			delta;
	t_weapon		*weapon;

	weapon = cub3d->player->current_weapon;
	current_time = get_timestamp();
	if (weapon->current_ammo == 0 && weapon->index != 1)
		return (finish_shooting(cub3d, anim), 0);
	delta = current_time - cub3d->prev_shoot;
	if (delta > weapon->fire_rate && weapon->index != 1)
	{
		if (weapon->current_ammo - 1 <= 0)
			ft_log("Out of ammo", NULL, 2);
		weapon->current_ammo--;
		cub3d->prev_shoot = current_time;
	}
	if (current_time - anim->last_update > anim->frame_delay)
		change_frame(cub3d, anim, current_time);
	return (0);
}
