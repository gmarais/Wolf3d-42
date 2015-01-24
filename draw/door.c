/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:51:30 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 19:55:35 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		calc_door_dist(t_env *e, t_trac_data *d, t_obj *ray)
{
	d->door_hit = 1;
	if (d->side == 0)
		d->perp_door_dist = fabs((d->map_x - ray->pos_x
									+ (1 - d->step_x) / 2) / ray->dir_x);
	else
		d->perp_door_dist = fabs((d->map_y - ray->pos_y
									+ (1 - d->step_y) / 2) / ray->dir_y);
	d->dline_height = ft_abs((int)(SCREEN_HEIGHT / d->perp_door_dist));
	d->door_type = ft_atoi((char *)&e->world[d->map_x][d->map_y][1]);
	if (d->side == 1)
		d->door_x = ray->pos_x
			+ ((d->map_y - ray->pos_y
				+ (1 - d->step_y) / 2) / ray->dir_y) * ray->dir_x;
	else
		d->door_x = ray->pos_y
			+ ((d->map_x - ray->pos_x
				+ (1 - d->step_x) / 2) / ray->dir_x) * ray->dir_y;
	d->door_x -= floor((d->door_x));
	d->dtex_x = (int)(d->door_x * (double)(TEX_WIDTH));
	if (d->side == 0 && ray->dir_x > 0)
		d->dtex_x = TEX_WIDTH - d->dtex_x - 1;
	if (d->side == 1 && ray->dir_y < 0)
		d->dtex_x = TEX_WIDTH - d->dtex_x - 1;
}

void		draw_door(t_env *e, t_trac_data *d)
{
	int				i;
	t_colors		col;

	d->draw_start = -d->dline_height / 2 + SCREEN_HEIGHT / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = d->dline_height / 2 + SCREEN_HEIGHT / 2;
	if (d->draw_end > SCREEN_HEIGHT)
		d->draw_end = SCREEN_HEIGHT;
	i = d->draw_start - 1;
	d->dtex_x -= e->door;
	while (++i < d->draw_end)
	{
		get_door_color(e, d, i, &col);
		if (col.b || col.g || col.r)
		{
			e->data[i * e->sizeline + d->x * (e->bpp / 8)] = col.b;
			e->data[i * e->sizeline + d->x * (e->bpp / 8) + 1] = col.g;
			e->data[i * e->sizeline + d->x * (e->bpp / 8) + 2] = col.r;
		}
	}
}

void		get_door_color(t_env *e, t_trac_data *d, int i, t_colors *col)
{
	int				dec;

	if (d->dtex_x < 0)
	{
		col->b = 0;
		col->g = 0;
		col->r = 0;
		return ;
	}
	dec = i * 256 - SCREEN_HEIGHT * 128 + d->dline_height * 128;
	d->tex_y = ((dec * TEX_HEIGHT) / d->dline_height) / 256;
	col->b = e->tex_tab[19].data[(d->tex_y * e->tex_tab[19].sizeline
									+ e->tex_tab[19].bpp / 8
									* d->dtex_x)];
	col->g = e->tex_tab[19].data[(d->tex_y * e->tex_tab[19].sizeline
									+ e->tex_tab[19].bpp / 8
									* d->dtex_x) + 1];
	col->r = e->tex_tab[19].data[(d->tex_y * e->tex_tab[19].sizeline
									+ e->tex_tab[19].bpp / 8
									* d->dtex_x) + 2];
}
