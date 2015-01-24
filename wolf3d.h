/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/18 18:50:30 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 19:41:35 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include <libft.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include <X11/X.h>

# define PI 3.14159265359
# define SCREEN_WIDTH 1024
# define SCREEN_HEIGHT 768
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define SKY_WIDTH 900
# define SKY_HEIGHT 90

typedef struct	s_cnt
{
	int			i;
	int			j;
	int			k;
}				t_cnt;

typedef struct	s_mv_dir
{
	int			fwd;
	int			bwd;
	int			rlft;
	int			rrgt;
	int			slft;
	int			srgt;
}				t_mv_dir;

typedef struct	s_trac_data
{
	double		camera_x;
	int			x;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			step_x;
	int			step_y;
	int			hit;
	int			door_hit;
	int			side;
	int			dside;
	double		perp_wall_dist;
	double		perp_door_dist;
	double		z_buffer[SCREEN_WIDTH];
	int			line_height;
	int			dline_height;
	int			wall_type;
	int			door_type;
	double		wall_x;
	double		door_x;
	int			tex_x;
	int			dtex_x;
	int			tex_y;
	int			tex_id;
	double		floor_x_wall;
	double		floor_y_wall;
	double		dist_wall;
	double		dist_player;
	double		current_dist;
	double		weight;
	double		current_floor_x;
	double		current_floor_y;
	int			draw_start;
	int			draw_end;
}				t_trac_data;

typedef	struct	s_obj
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
	int			life;
	int			dist;
	int			tex_id;
}				t_obj;

typedef struct		s_tex
{
	void			*img;
	char			*data;
	int				bpp;
	int				sizeline;
	int				endian;
}					t_tex;

typedef struct		s_env
{
	struct s_tex	end_screen[3];
	int				key;
	int				op;
	int				vict;
	int				door;
	int				sprites_nbr;
	struct s_obj	*sprite_tab;
	struct s_tex	tex_tab[20];
	struct s_tex	gun_tex[3];
	int				shooting;
	struct s_tex	skybox;
	void			*mlx;
	void			*win;
	void			*im_tmp;
	char			*data;
	int				bpp;
	int				sizeline;
	int				endian;
	char			***world;
	size_t			map_width;
	size_t			map_height;
	struct s_obj	p;
	struct s_mv_dir	move;
}					t_env;

typedef	struct		s_colors
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_colors;

typedef	struct		s_gather
{
	size_t			x;
	size_t			y;
	char			*line;
	int				fd;
	int				bol;
}					t_gather;

typedef struct		s_spricast
{
	double			trans_x;
	double			trans_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				sprite_width;
	int				draw_start_y;
	int				draw_end_y;
	int				y;
	t_colors		col;
	int				i;
}					t_spricast;

void		ft_pixel_put_to_img(t_env *e, int x, int y, int color);
void		dead_clear_img(t_env *e);
void		get_end_color(t_env	*e, int  i, int  j, t_colors *col);
void		put_end(t_env *e, int i, int j, t_colors *col);
void		end_to_img(t_env *e);
void		get_door_color(t_env *e, t_trac_data *d, int i, t_colors *col);
void		get_pixel_color(t_env *e, t_trac_data *d, int i, t_colors *col);
void		apply_shadow(t_trac_data *d, t_obj *ray, t_colors *col);
void		ft_swap_objtab(t_env *e, int *i, int *j);
void		sort_tab(t_env *e);
void		init_sprite_tab(t_env *e);
void		set_trans_xy(t_env *e, t_spricast *va);
void		set_sprite_draw_strt_nd(t_spricast *va,  t_trac_data *d, t_env *e);
void		pimp_my_sprite(t_env *e, t_trac_data *d, t_spricast *va);
void		sprite_in_img(t_env *e, t_trac_data *d, t_spricast *va);
void		print_my_sprite(t_env *e, t_trac_data *d, t_spricast *va);
void		get_gun_color(t_env	*e, int  i, int  j, t_colors *col);
void		put_gun(t_env *e, int i, int j, t_colors *col);
void		gun_to_img(t_env *e);
int			colision_check(t_env *e, double x, double y);
void		remove_one_obj_tab(t_env *e, int i);
void		apply_damages(t_env *e, int check, int *i);
int			damage_player(t_env *e, int *i);
void		move_bullets(t_env *e);
void		add_one_obj_tab(t_env *e);
void		showgun(t_env *e);
void		sprite_casting(t_env *e, t_trac_data *d);
void		floor_pixel_color(t_env *e, int x, int y, t_colors *col);
void		print_floor(t_env *e, t_trac_data *d, t_colors *col, int y);
void		draw_floor(t_env *e, t_trac_data *d);
void		get_floor(t_env *e, t_trac_data *d, t_obj *ray);
double		vdir_to_degree(double dir_x, double dir_y);
void		draw_skybox(t_env *e, t_trac_data *d, t_obj *ray);
void		draw_door(t_env *e, t_trac_data *d);
void		draw_wall(t_env *e, t_trac_data *d, t_obj *ray);
void		tracing_and_ray_init(t_env *e, t_trac_data *d, t_obj *ray);
void		calculating_steps(t_trac_data *d, t_obj *ray);
void		calc_door_dist(t_env *e, t_trac_data *d, t_obj *ray);
void		searching_wall(t_env *e, t_trac_data *d, t_obj *ray);
void		calculating_distances(t_env *e, t_trac_data *d, t_obj *ray);
void		apply_strafing(t_env *e);
void		apply_rot(t_env *e);
void		apply_move(t_env *e);
void		apply_teleport(t_env *e);
void		shoot(t_env *e);
void		move_sprite(t_env *e, int i);
void		monsters_attack(t_env *e, int i, double dist);
void		open_door(t_env *e);
void		basic_ai(t_env *e);
void		eat_cookies(t_env *e);
void		check_victory(t_env *e);
void		put_img(t_env *e);
void		init_moves(t_env *e);
int			draw(t_env *e);
int			key_hook_r(int keycode, t_env *e);
int			key_hook(int keycode, t_env *e);
int			expose_hook(t_env *e);
int			numsize(char *str, int i);
int			get_world_size(size_t *max_x, size_t *max_y, char *path);
int			world_alloc(t_env *e, int max_x, int max_y);
int			world_init(t_env *e, char *path);
int			create_world(t_env *e, char *path);
int			set_sprite_num(t_env *e, char *path, t_gather *var);
void		init_sprite_var(t_env *e, t_gather *var);
int			gather_sprites(t_env *e, char *path);
int			text_load(t_env *e, t_tex *image, char *file);
int			load_skybox(t_env *e, t_tex *image, char *file);
int			load_end_screens(t_env *e, t_tex *image, char *file);
int			text_loader(t_env *e);
int			interface_loader(t_env *e);
void		print_world(t_env *e);
void		player_init(t_env *e);
void		patch_sprite_tab(t_env *e);
void		teleport_bis(t_env *e);
void		teleport_bis_bis(t_env *e);
void		world_assign(t_env *e, t_cnt *c, char *line);

#endif /*!WOLF3D_H*/
