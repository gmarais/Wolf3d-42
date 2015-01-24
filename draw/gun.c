/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:44:20 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 19:58:34 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		get_gun_color(t_env *e, int i, int j, t_colors *col)
{
	int		id;

	id = (e->shooting) ? 1 : 0;
	col->b = ((e->gun_tex)[id].data)[(j * (e->gun_tex)[id].sizeline
										+ ((e->gun_tex)[id].bpp / 8) * i)];
	col->g = ((e->gun_tex)[id].data)[(j * (e->gun_tex)[id].sizeline
										+ ((e->gun_tex)[id].bpp / 8) * i) + 1];
	col->r = ((e->gun_tex)[id].data)[(j * (e->gun_tex)[id].sizeline
										+ ((e->gun_tex)[id].bpp / 8) * i) + 2];
}

void		put_gun(t_env *e, int i, int j, t_colors *col)
{
	e->data[i * e->sizeline + j * (e->bpp / 8)] = col->b;
	e->data[i * e->sizeline + j * (e->bpp / 8) + 1] = col->g;
	e->data[i * e->sizeline + j * (e->bpp / 8) + 2] = col->r;
}

void		gun_to_img(t_env *e)
{
	int			i;
	int			j;
	t_colors	col;

	j = SCREEN_WIDTH / 2 - SCREEN_WIDTH / 10;
	while (++j < SCREEN_WIDTH / 2 + SCREEN_WIDTH / 10)
	{
		i = SCREEN_HEIGHT - SCREEN_HEIGHT / 4;
		while (++i < SCREEN_HEIGHT)
		{
			get_gun_color(e, (j - (SCREEN_WIDTH / 2.0 - SCREEN_WIDTH / 10.0))
							/ ((SCREEN_WIDTH / 2.0 + SCREEN_WIDTH / 10.0)
							- (SCREEN_WIDTH / 2.0 - SCREEN_WIDTH / 10.0))
							* TEX_WIDTH, (i - (SCREEN_HEIGHT - SCREEN_HEIGHT
												/ 4.0))
							/ (SCREEN_HEIGHT - (SCREEN_HEIGHT - SCREEN_HEIGHT
												/ 4.0))
							* TEX_HEIGHT, &col);
			if (col.b || col.g || col.r)
				put_gun(e, i, j, &col);
		}
	}
}

void		showgun(t_env *e)
{
	static int	ct = 0;

	move_bullets(e);
	if (ct == 5 && !(ct = 0))
		e->shooting = 0;
	if (e->shooting == 1)
	{
		ct++;
		if (ct == 1)
		{
			add_one_obj_tab(e);
			e->sprite_tab[e->sprites_nbr - 1].life = 0;
			e->sprite_tab[e->sprites_nbr - 1].pos_x = e->p.pos_x
				+ 0.5 * e->p.dir_x;
			e->sprite_tab[e->sprites_nbr - 1].pos_y = e->p.pos_y
				+ 0.5 * e->p.dir_y;
			e->sprite_tab[e->sprites_nbr - 1].dir_x = e->p.dir_x;
			e->sprite_tab[e->sprites_nbr - 1].dir_y = e->p.dir_y;
			e->sprite_tab[e->sprites_nbr - 1].plane_x = 0;
			e->sprite_tab[e->sprites_nbr - 1].plane_y = 1;
			e->sprite_tab[e->sprites_nbr - 1].tex_id = 13;
		}
	}
}
