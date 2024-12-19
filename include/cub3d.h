/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student@42Warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 13:26:15 by msolinsk          #+#    #+#             */
/*   Updated: 2024/12/19 22:22:05 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "structs.h"
# include <math.h>
# include <mlx.h>
# include <mlx_int.h>
# include <stdio.h>

# define KEY_ESC 65307
# define ON_DESTROY 17
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_SPACE 32
# define STEP_SPEED 0.05
# define MOVE_SPEED 0.02
# define ROT_SPEED 0.02
# define FLOOR 6
# define CEILING 7

//      DEFINE FRAME RATE TO 0 (or less) TO DISABLE FRAME RATE LIMITING
# define FRAME_RATE -1
# define OFFSET 5

//      RAYCASTER.C
int				raycaster(t_cub3d *cub3d);
int				get_pixel_color(t_sprite *sprite, int x, int y);

//      DRAW_WALL.C
int				find_texnum(t_cub3d *cub3d, t_ray *ray);
double			get_wallx(t_ray *ray, t_cub3d *cub3d);
void			draw_wall(t_cub3d *cub3d, t_ray *ray, int *int_vars,
					double wallx);

//      RAY_UTILS.C
int				init_ray(t_ray *ray, t_cub3d *cub3d, int x);
void			cast_ray(t_cub3d *cub3d, t_ray *ray);
void			perpwalldist(t_ray *ray);

//      DRAW_CEIL_FLOOR.C
void			draw_ceil_floor(t_cub3d *cub3d, int *int_vars);

//      MAIN.C
int				main_loop(t_cub3d *cub3d);
int				ft_exit(t_cub3d *cub3d);

//      INIT.C
int				ft_init_cub3d(t_cub3d *cub3d, char **argv);
void			ft_set_default_state(t_cub3d *cub3d);

//      FT_IMAGES.C
void			ft_print_img_info(t_sprite *img);
t_sprite		**ft_load_sprites(t_cub3d *cub3d);
t_sprite		*xpm_load_image(void *mlx, char *path, int sub_level);
void			ft_free_sprites(t_cub3d *cub3d);
t_sprite		*ft_scale_sprite(t_cub3d *cub3d, t_sprite *src, int new_width,
					int new_height);
t_sprite		*ft_create_blank(t_cub3d *cub3d, int width, int height);

//      ANIM.C
int				update_animation(t_cub3d *cub3d, t_anim *anim);
void			ft_anim(t_cub3d *cub3d);
t_anim			*ft_load_anim(t_cub3d *cub3d, char *folder_path);
t_anim			**ft_load_anims(t_cub3d *cub3d);
void			draw_sprite_to_buffer(t_cub3d *cub3d, t_sprite *sprite,
					int x_offset, int y_offset);

//      ANIM_UTILS.C
int				ft_get_dir_count(char *path);
char			**ft_get_dir_files(char *path);
char			**ft_string_sort(char **names);
t_sprite		**load_batch(t_cub3d *cub3d, char *dir_path);
t_sprite		**load_scale(t_cub3d *cub3d, char **names, t_sprite **imgs,
					char *dir);

//      FT_DRAW.C
void			put_pixel_to_img(t_sprite *img, int x, int y, int color);
void			draw_sprite_to_HUD(t_cub3d *cub3d, t_sprite *sprite,
					int x_offset, int y_offset);
void			draw_2_buffer(t_sprite *dest, t_sprite *src, int x_offset,
					int y_offset);
void			blend_pixel(t_sprite *dest, t_sprite *src, t_vec2 v,
					t_vec2 off);
int				is_within_bounds(t_sprite *img, int x, int y);

//      FT_MINIMAP.C
void			ft_draw_minimap(t_cub3d *cub3d, int px, int py);

//      FT_LOGS.C
void			ft_log(char *str, char *str_optional, int level);
void			ft_log_sub(char *str, char *str_optional, int level,
					int sub_level);

//      FT_MAP_LOAD.C
t_map			*ft_load_map(t_cub3d *cub3d, char *path);
void			ft_process_grid(t_cub3d *cub3d, t_map *map, char *line, int y);
void			ft_north_south(t_player *player, char direction);
void			ft_east_west(t_player *player, char direction);
void			ft_set_player_position(t_player *player, int x, int y,
					char **grid);
void			ft_load_texture(t_cub3d *cub3d, t_map *map, char **split,
					int index);
void			ft_load_color(t_map *map, char **split, int index);
int				ft_get_map_height(char *path);
void			ft_handle_split(t_map *map, char **split, int *i,
					t_cub3d *cub3d);
int				ft_check_map_closed(t_map *map);
int				ft_check_if_map_valid(t_map *map);

//      GNL.C
char			*get_next_line(int fd);

//      UTILS.C
unsigned long	rgb_to_hex(int r, int g, int b);
int				ft_2d_len(void **array);
long			get_timestamp(void);
void			ft_assign_mlx(t_cub3d *cub3d, void *mlx, void *win);
int				check_args(int argc, char **argv);

//      FT_FREE.C
void			ft_free_all(t_cub3d *cub3d);
void			ft_free_sprite(t_cub3d *cub3d, t_sprite *sprite);
void			ft_free_2d_array(char **array);
void			ft_free_animations(t_cub3d *cub3d);
void			ft_free_font(t_cub3d *cub3d);
void			ft_free_map(t_map *map);

// INPUT.C
void			handle_input(t_cub3d *cub3d);
void			move_left(t_cub3d *cub3d);
void			move_right(t_cub3d *cub3d);
void			move_forward(t_cub3d *cub3d);
void			move_backward(t_cub3d *cub3d);
void			rotate_left(t_cub3d *cub3d);
void			rotate_right(t_cub3d *cub3d);
int				ft_key_press(int keycode, t_cub3d *cub3d);
int				ft_key_release(int keycode, t_cub3d *cub3d);
void			look_up(t_cub3d *cub3d);
void			look_down(t_cub3d *cub3d);

// SPLASH_SCREEN.C
int				splash_screen(t_cub3d *cub3d);
void			change_sprite_transparency(t_sprite *sprite,
					unsigned char transparency);

// HUD.C
void			ft_render_hud(t_cub3d *cub3d, double frame_time);
void			ft_render_health(t_cub3d *cub3d);
void			ft_render_ammo(t_cub3d *cub3d);
void			ft_render_weapon(t_cub3d *cub3d);
void			ft_render_framerate(t_cub3d *cub3d, double frame_time);

// FONT_RENDERER.C
t_font			**load_font(t_cub3d *cub3d, char *path, int font_size);
void			draw_font(t_cub3d *cub3d, char *str, int x, int y);

// DOOR.C
void			update_doors(t_cub3d *cub3d);
int				try_open_door(t_cub3d *cub3d);
void			init_door_system(t_cub3d *cub3d);
void			open_existing_door(t_cub3d *cub3d, int nx, int ny);
void			add_new_door(t_cub3d *cub3d, int nx, int ny);

//      WEAPONS.C
void			init_weapons(t_cub3d *cub3d);

//  MOUSE.C
int				mouse_move(int x, int y, t_cub3d *cub3d);
int				mouse_press(int button, int x, int y, t_cub3d *cub3d);
int				mouse_release(int button, int x, int y, t_cub3d *cub3d);

//  KEYS.C
void			initialize_keys(t_cub3d *cub3d);

#endif