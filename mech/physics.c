/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/20 15:58:11 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 21:03:32 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			colision_check(t_env *e, double x, double y)
{
	int		i;

	if (ft_atoi(e->world[(int)x][(int)y])
		|| (e->world[(int)x][(int)y][0] == 'D' && e->door != 64))
		return (-1);
	i = -1;
	while (i++ < e->sprites_nbr)
	{
		if (e->sprite_tab[i].life
			&& e->sprite_tab[i].plane_y != 1
			&& sqrt((e->sprite_tab[i].pos_x - x)
					* (e->sprite_tab[i].pos_x - x)
					+ (e->sprite_tab[i].pos_y - y)
					* (e->sprite_tab[i].pos_y - y))
			< 0.5)
			return (i + 1);
	}
	return (0);
}

void		open_door(t_env *e)
{
	if (e->op != 0 && e->key == 0)
		e->op = 0;
	if (e->op != 0 && e->key != 0)
	{
		if (e->op > 0)
		{
			e->door = (e->door < 64) ? e->door + e->op : 64;
		}
		else if (e->op < 0)
		{
			e->door = (e->door > 0) ? e->door + e->op : 0;
		}
	}
}

void		eat_cookies(t_env *e)
{
	int			i;
	double		dist;

	i = -1;
	while (++i < e->sprites_nbr)
	{
		if (e->sprite_tab[i].tex_id == 14
			|| e->sprite_tab[i].tex_id == 15)
		{
			dist = sqrt((e->sprite_tab[i].pos_x - e->p.pos_x)
						* (e->sprite_tab[i].pos_x - e->p.pos_x)
						+ (e->sprite_tab[i].pos_y - e->p.pos_y)
						* (e->sprite_tab[i].pos_y - e->p.pos_y));
			if (dist < 1 && (e->p.life < 5 || e->sprite_tab[i].tex_id == 15))
			{
				if (e->sprite_tab[i].tex_id == 14)
					e->p.life = 5;
				if (e->sprite_tab[i].tex_id == 15)
					e->key = 1;
				remove_one_obj_tab(e, i);
				i = i - 1;
			}
		}
	}
}
