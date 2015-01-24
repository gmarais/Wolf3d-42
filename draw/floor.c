/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprcstfloor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/18 18:02:39 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/20 16:41:23 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		floor_pixel_color(t_env *e, int x, int y, t_colors *col)
{
	int		id;

	id = (e->p.pos_x > 25) ? 2 : 9;
	col->b = ((e->tex_tab)[id].data)[(y * (e->tex_tab)[id].sizeline
										+ ((e->tex_tab)[id].bpp / 8) * x)];
	col->g = ((e->tex_tab)[id].data)[(y * (e->tex_tab)[id].sizeline
										+ ((e->tex_tab)[id].bpp / 8) * x) + 1];
	col->r = ((e->tex_tab)[id].data)[(y * (e->tex_tab)[id].sizeline
										+ ((e->tex_tab)[id].bpp / 8) * x) + 2];
}

void		print_floor(t_env *e, t_trac_data *d, t_colors *col, int y)
{
	e->data[y * e->sizeline + d->x * (e->bpp / 8)] = col->b;
	e->data[y * e->sizeline + d->x * (e->bpp / 8) + 1] = col->g;
	e->data[y * e->sizeline + d->x * (e->bpp / 8) + 2] = col->r;
	if (e->p.pos_x > 25)
	{
		e->data[(SCREEN_HEIGHT - (y + 1)) * e->sizeline
				+ d->x * (e->bpp / 8)] = col->b * 1.25;
		e->data[(SCREEN_HEIGHT - (y + 1)) * e->sizeline
				+ d->x * (e->bpp / 8) + 1] = col->g * 1.25;
		e->data[(SCREEN_HEIGHT - (y + 1)) * e->sizeline
				+ d->x * (e->bpp / 8) + 2] = col->r * 1.25;
	}
}

void		draw_floor(t_env *e, t_trac_data *d)
{
	int				floor_tex_x;
	int				floor_tex_y;
	int				y;
	t_colors		col;

	d->dist_wall = d->perp_wall_dist;
	d->dist_player = 0.0;
	if (d->draw_end < 0)
		d->draw_end = SCREEN_HEIGHT;
	y = d->draw_end - 1;
	while (++y < SCREEN_HEIGHT)
	{
		d->current_dist = SCREEN_HEIGHT / (2.0 * y - SCREEN_HEIGHT);
		d->weight = (d->current_dist - d->dist_player)
			/ (d->dist_wall - d->dist_player);
		d->current_floor_x = d->weight * d->floor_x_wall
			+ (1.0 - d->weight) * e->p.pos_x;
		d->current_floor_y = d->weight * d->floor_y_wall
			+ (1.0 - d->weight) * e->p.pos_y;
		floor_tex_x = ft_abs((int)(d->current_floor_x * TEX_WIDTH) % TEX_WIDTH);
		floor_tex_y = ft_abs((int)(d->current_floor_y
									* TEX_HEIGHT) % TEX_HEIGHT);
		floor_pixel_color(e, floor_tex_x, floor_tex_y, &col);
		print_floor(e, d, &col, y);
	}
}

void		get_floor(t_env *e, t_trac_data *d, t_obj *ray)
{
	if (d->side == 0 && ray->dir_x > 0)
	{
		d->floor_x_wall = d->map_x;
		d->floor_y_wall = d->map_y + d->wall_x;
	}
	else if (d->side == 0 && ray->dir_x < 0)
	{
		d->floor_x_wall = d->map_x + 1.0;
		d->floor_y_wall = d->map_y + d->wall_x;
	}
	else if (d->side == 1 && ray->dir_y > 0)
	{
		d->floor_x_wall = d->map_x + d->wall_x;
		d->floor_y_wall = d->map_y;
	}
	else
	{
		d->floor_x_wall = d->map_x + d->wall_x;
		d->floor_y_wall = d->map_y + 1.0;
	}
	draw_floor(e, d);
}
