/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:50:25 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 20:03:25 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		apply_shadow(t_trac_data *d, t_obj *ray, t_colors *col)
{
	if (d->side == 1 || (d->side == 0 && ray->dir_x >= 0))
	{
		if (d->side == 0)
		{
			col->b = (int)(col->b / 1.5);
			col->g = (int)(col->g / 1.5);
			col->r = (int)(col->r / 1.5);
		}
		else if (d->side == 1 && ray->dir_y >= 0)
		{
			col->b = (int)(col->b / 1.10);
			col->g = (int)(col->g / 1.10);
			col->r = (int)(col->r / 1.10);
		}
		else
		{
			col->b = (int)(col->b / 1.25);
			col->g = (int)(col->g / 1.25);
			col->r = (int)(col->r / 1.25);
		}
	}
}

void		searching_wall(t_env *e, t_trac_data *d, t_obj *ray)
{
	while (d->hit == 0)
	{
		if (d->side_dist_x < d->side_dist_y)
		{
			d->side_dist_x += d->delta_dist_x;
			d->map_x += d->step_x;
			d->side = 0;
		}
		else
		{
			d->side_dist_y += d->delta_dist_y;
			d->map_y += d->step_y;
			d->side = 1;
		}
		if (ft_atoi(e->world[d->map_x][d->map_y]))
			d->hit = 1;
		if (e->world[d->map_x][d->map_y][0] == 'D')
			calc_door_dist(e, d, ray);
	}
}

void		calculating_distances(t_env *e, t_trac_data *d, t_obj *ray)
{
	if (d->side == 0)
		d->perp_wall_dist = fabs((d->map_x - ray->pos_x
									+ (1 - d->step_x) / 2) / ray->dir_x);
	else
		d->perp_wall_dist = fabs((d->map_y - ray->pos_y
									+ (1 - d->step_y) / 2) / ray->dir_y);
	d->line_height = ft_abs((int)(SCREEN_HEIGHT / d->perp_wall_dist));
	d->wall_type = ft_atoi(e->world[d->map_x][d->map_y]);
	if (d->side == 1)
		d->wall_x = ray->pos_x
			+ ((d->map_y - ray->pos_y
				+ (1 - d->step_y) / 2) / ray->dir_y) * ray->dir_x;
	else
		d->wall_x = ray->pos_y
			+ ((d->map_x - ray->pos_x
				+ (1 - d->step_x) / 2) / ray->dir_x) * ray->dir_y;
	d->wall_x -= floor((d->wall_x));
	d->tex_x = (int)(d->wall_x * (double)(TEX_WIDTH));
	if (d->side == 0 && ray->dir_x > 0)
		d->tex_x = TEX_WIDTH - d->tex_x - 1;
	if (d->side == 1 && ray->dir_y < 0)
		d->tex_x = TEX_WIDTH - d->tex_x - 1;
}

void		draw_wall(t_env *e, t_trac_data *d, t_obj *ray)
{
	int				i;
	t_colors		col;

	d->draw_start = -d->line_height / 2 + SCREEN_HEIGHT / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = d->line_height / 2 + SCREEN_HEIGHT / 2;
	if (d->draw_end > SCREEN_HEIGHT)
		d->draw_end = SCREEN_HEIGHT;
	i = d->draw_start - 1;
	while (++i < d->draw_end)
	{
		get_pixel_color(e, d, i, &col);
		apply_shadow(d, ray, &col);
		if ((d->tex_id != 1 && d->tex_id != 0) || col.b || col.g || col.r)
		{
			e->data[i * e->sizeline + d->x * (e->bpp / 8)] = col.b;
			e->data[i * e->sizeline + d->x * (e->bpp / 8) + 1] = col.g;
			e->data[i * e->sizeline + d->x * (e->bpp / 8) + 2] = col.r;
		}
	}
}
