/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_move2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/18 18:15:07 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 20:04:25 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		move_sprite(t_env *e, int i)
{
	if ((int)(e->sprite_tab[i].pos_x * 100) < (int)(e->p.pos_x * 100)
		&& !colision_check(e, e->sprite_tab[i].pos_x
							+ 0.5, e->sprite_tab[i].pos_y))
		e->sprite_tab[i].pos_x += 0.02;
	else if ((int)(e->sprite_tab[i].pos_x * 100)
				> (int)(e->p.pos_x * 100)
				&& !colision_check(e, e->sprite_tab[i].pos_x
									- 0.5, e->sprite_tab[i].pos_y))
		e->sprite_tab[i].pos_x -= 0.02;
	if ((int)(e->sprite_tab[i].pos_y * 100) < (int)(e->p.pos_y * 100)
		&& !colision_check(e, e->sprite_tab[i].pos_x
							, e->sprite_tab[i].pos_y + 0.5))
		e->sprite_tab[i].pos_y += 0.02;
	else if ((int)(e->sprite_tab[i].pos_y * 100)
				> (int)(e->p.pos_y * 100)
				&& !colision_check(e, e->sprite_tab[i].pos_x
									, e->sprite_tab[i].pos_y - 0.5))
		e->sprite_tab[i].pos_y -= 0.02;
}

void		monsters_attack(t_env *e, int i, double dist)
{
	add_one_obj_tab(e);
	e->sprite_tab[e->sprites_nbr - 1].life = 0;
	e->sprite_tab[e->sprites_nbr - 1].pos_x = e->sprite_tab[i].pos_x;
	e->sprite_tab[e->sprites_nbr - 1].pos_y = e->sprite_tab[i].pos_y;
	e->sprite_tab[e->sprites_nbr
					- 1].dir_x = ((e->p.pos_x
									- e->sprite_tab[i].pos_x) / dist) * 0.5;
	e->sprite_tab[e->sprites_nbr
					- 1].dir_y = ((e->p.pos_y
									- e->sprite_tab[i].pos_y) / dist) * 0.5;
	e->sprite_tab[e->sprites_nbr - 1].plane_x = 2;
	e->sprite_tab[e->sprites_nbr - 1].plane_y = 1;
	e->sprite_tab[e->sprites_nbr - 1].tex_id = 13;
}

void		basic_ai(t_env *e)
{
	int				i;
	static int		ct = 0;
	double			dist;

	open_door(e);
	i = -1;
	ct = (ct == 40) ? 0 : ct + 1;
	while (++i < e->sprites_nbr && !(e->vict))
	{
		if (e->sprite_tab[i].life)
		{
			dist = sqrt((e->sprite_tab[i].pos_x - e->p.pos_x)
						* (e->sprite_tab[i].pos_x - e->p.pos_x)
						+ (e->sprite_tab[i].pos_y - e->p.pos_y)
						* (e->sprite_tab[i].pos_y - e->p.pos_y));
			if (ct == 40 && (dist < 10 || e->sprite_tab[i].life < 5))
				monsters_attack(e, i, dist);
			if ((dist < 10 || e->sprite_tab[i].life < 5) && dist > 1)
			{
				e->sprite_tab[i].plane_y = 1;
				move_sprite(e, i);
				e->sprite_tab[i].plane_y = 0;
			}
		}
	}
}
