/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:47:24 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 19:56:51 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		put_img(t_env *e)
{
	if (e->p.life < 5)
		dead_clear_img(e);
	check_victory(e);
	if (!e->p.life && !e->vict)
	{
		e->move.fwd = 0;
		e->move.bwd = 0;
		e->move.rlft = 0;
		e->move.rrgt = 0;
		e->move.slft = 0;
		e->move.srgt = 0;
		end_to_img(e);
	}
	mlx_put_image_to_window(e->mlx, e->win, e->im_tmp, 0, 0);
}

void		tracing_and_ray_init(t_env *e, t_trac_data *d, t_obj *ray)
{
	d->camera_x = 2 * d->x / (double)(SCREEN_WIDTH) - 1;
	ray->pos_x = e->p.pos_x;
	ray->pos_y = e->p.pos_y;
	ray->dir_x = e->p.dir_x + e->p.plane_x * d->camera_x;
	ray->dir_y = e->p.dir_y + e->p.plane_y * d->camera_x;
	d->map_x = (int)(ray->pos_x);
	d->map_y = (int)(ray->pos_y);
	d->delta_dist_x = sqrt((1 + (ray->dir_y * ray->dir_y)
							/ (ray->dir_x * ray->dir_x)));
	d->delta_dist_y = sqrt((1 + (ray->dir_x * ray->dir_x)
							/ (ray->dir_y * ray->dir_y)));
	d->hit = 0;
	d->door_hit = 0;
}

void		calculating_steps(t_trac_data *d, t_obj *ray)
{
	if (ray->dir_x < 0)
	{
		d->step_x = -1;
		d->side_dist_x = (ray->pos_x - d->map_x) * d->delta_dist_x;
	}
	else
	{
		d->step_x = 1;
		d->side_dist_x = (d->map_x + 1.0 - ray->pos_x) * d->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		d->step_y = -1;
		d->side_dist_y = (ray->pos_y - d->map_y) * d->delta_dist_y;
	}
	else
	{
		d->step_y = 1;
		d->side_dist_y = (d->map_y + 1.0 - ray->pos_y) * d->delta_dist_y;
	}
}

void		init_moves(t_env *e)
{
	basic_ai(e);
	apply_rot(e);
	apply_move(e);
	apply_strafing(e);
	eat_cookies(e);
}

int			draw(t_env *e)
{
	t_trac_data	d;
	t_obj		ray;

	init_moves(e);
	d.x = -1;
	while (++(d.x) < SCREEN_WIDTH)
	{
		tracing_and_ray_init(e, &d, &ray);
		calculating_steps(&d, &ray);
		searching_wall(e, &d, &ray);
		calculating_distances(e, &d, &ray);
		d.tex_id = d.wall_type - 1;
		d.tex_id = (d.tex_id > 18) ? 0 : d.tex_id;
		if (e->p.pos_x < 25)
			draw_skybox(e, &d, &ray);
		draw_wall(e, &d, &ray);
		get_floor(e, &d, &ray);
		if (d.door_hit)
			draw_door(e, &d);
		d.z_buffer[d.x] = (d.door_hit && d.dtex_x > 0) ? d.perp_door_dist
			: d.perp_wall_dist;
	}
	sprite_casting(e, &d);
	put_img(e);
	return (0);
}
