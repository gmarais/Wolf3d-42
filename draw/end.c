/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/18 17:48:47 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 19:57:32 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		dead_clear_img(t_env *e)
{
	int			i;
	int			j;
	t_colors	col;
	int			color;

	i = -1;
	while (++i < SCREEN_HEIGHT)
	{
		j = -1;
		while (++j < SCREEN_WIDTH)
		{
			col.b = e->data[i * e->sizeline + e->bpp / 8 * j];
			col.g = e->data[i * e->sizeline + e->bpp / 8 * j + 1];
			col.r = e->data[i * e->sizeline + e->bpp / 8 * j + 2];
			color = col.b / (6 - e->p.life)
				+ (col.g / (6 - e->p.life)) * 256
				+ (col.r) * 65536;
			ft_pixel_put_to_img(e, j, i, color);
		}
	}
}

void		get_end_color(t_env *e, int i, int j, t_colors *col)
{
	int		id;

	id = (e->p.life) ? 1 : 0;
	col->b = ((e->end_screen)[id].data)[(j * (e->end_screen)[id].sizeline
										+ ((e->end_screen)[id].bpp / 8) * i)];
	col->g = ((e->end_screen)[id].data)[(j * (e->end_screen)[id].sizeline
										+ ((e->end_screen)[id].bpp
											/ 8) * i) + 1];
	col->r = ((e->end_screen)[id].data)[(j * (e->end_screen)[id].sizeline
										+ ((e->end_screen)[id].bpp
											/ 8) * i) + 2];
}

void		put_end(t_env *e, int i, int j, t_colors *col)
{
	e->data[i * e->sizeline + j * (e->bpp / 8)] = col->b;
	e->data[i * e->sizeline + j * (e->bpp / 8) + 1] = col->g;
	e->data[i * e->sizeline + j * (e->bpp / 8) + 2] = col->r;
}

void		end_to_img(t_env *e)
{
	int			i;
	int			j;
	t_colors	col;

	j = -1;
	while (++j < SCREEN_WIDTH)
	{
		i = SCREEN_HEIGHT / 2 - SCREEN_HEIGHT / 5;
		while (++i < SCREEN_HEIGHT / 2 + SCREEN_HEIGHT / 5)
		{
			get_end_color(e, (double)j / SCREEN_WIDTH * 320
							, (i - (SCREEN_HEIGHT / 2.0 - SCREEN_HEIGHT / 5.0))
							/ ((SCREEN_HEIGHT / 2.0 + SCREEN_HEIGHT / 5.0)
								- (SCREEN_HEIGHT / 2.0 - SCREEN_HEIGHT / 5.0))
							* 64, &col);
			if (col.b || col.g || col.r)
				put_end(e, i, j, &col);
		}
	}
}
