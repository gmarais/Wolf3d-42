/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skybox.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 16:40:15 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/20 16:41:43 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		draw_skybox(t_env *e, t_trac_data *d, t_obj *ray)
{
	int				i;
	int				sky_x;
	int				sky_y;
	t_colors		col;

	sky_x = (int)vdir_to_degree(ray->dir_x, ray->dir_y);
	sky_x = (int)(((double)sky_x / 360.0) * SKY_WIDTH);
	sky_x = SKY_WIDTH - sky_x;
	i = 0;
	while (i < SCREEN_HEIGHT / 2)
	{
		sky_y = ((double)i / ((double)SCREEN_HEIGHT / 2.0)) * SKY_HEIGHT;
		col.b = e->skybox.data[sky_y * e->skybox.sizeline
								+ (e->skybox.bpp / 8) * sky_x];
		col.g = e->skybox.data[sky_y * e->skybox.sizeline
								+ (e->skybox.bpp / 8) * sky_x + 1];
		col.r = e->skybox.data[sky_y * e->skybox.sizeline
								+ (e->skybox.bpp / 8) * sky_x + 2];
		e->data[i * e->sizeline + d->x * (e->bpp / 8)] = col.b;
		e->data[i * e->sizeline + d->x * (e->bpp / 8) + 1] = col.g;
		e->data[i * e->sizeline + d->x * (e->bpp / 8) + 2] = col.r;
		i++;
	}
}
