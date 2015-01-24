/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_usage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 13:59:10 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 20:01:11 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_pixel_put_to_img(t_env *e, int x, int y, int color)
{
	unsigned long	img_color;
	t_colors		col;

	img_color = mlx_get_color_value(e->mlx, color);
	col.r = ((img_color & 0xFF0000) >> 16);
	col.g = ((img_color & 0xFF00) >> 8);
	col.b = ((img_color & 0xFF));
	e->data[y * e->sizeline + x * e->bpp / 8] = col.b;
	e->data[y * e->sizeline + x * e->bpp / 8 + 1] = col.g;
	e->data[y * e->sizeline + x * e->bpp / 8 + 2] = col.r;
}

void		get_pixel_color(t_env *e, t_trac_data *d, int i, t_colors *col)
{
	int				dec;

	dec = i * 256 - SCREEN_HEIGHT * 128 + d->line_height * 128;
	d->tex_y = ((dec * TEX_HEIGHT) / d->line_height) / 256;
	col->b = e->tex_tab[d->tex_id].data[(d->tex_y
											* e->tex_tab[d->tex_id].sizeline
											+ e->tex_tab[d->tex_id].bpp / 8
											* d->tex_x)];
	col->g = e->tex_tab[d->tex_id].data[(d->tex_y
											* e->tex_tab[d->tex_id].sizeline
											+ e->tex_tab[d->tex_id].bpp / 8
											* d->tex_x) + 1];
	col->r = e->tex_tab[d->tex_id].data[(d->tex_y
											* e->tex_tab[d->tex_id].sizeline
											+ e->tex_tab[d->tex_id].bpp / 8
											* d->tex_x) + 2];
}

double		vdir_to_degree(double dir_x, double dir_y)
{
	double	result;

	if (dir_x != 0)
		result = atan(dir_y / dir_x) * 180.0 / PI;
	else
	{
		if (dir_y > 0)
			result = 90;
		else
			result = -90;
	}
	if (result < 0)
		result = 180 + result;
	if (dir_y <= 0)
		result = 180 + result;
	return (result);
}
