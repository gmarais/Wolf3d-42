/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damages.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/18 18:00:15 by gmarais           #+#    #+#             */
/*   Updated: 2014/01/18 18:51:15 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		remove_one_obj_tab(t_env *e, int i)
{
	int		j;
	t_obj	*to_free;

	j = 0;
	to_free = e->sprite_tab;
	e->sprite_tab = (t_obj *)malloc(sizeof(t_obj) * e->sprites_nbr);
	while (j < i)
	{
		e->sprite_tab[j] = to_free[j];
		j++;
	}
	while (++j < e->sprites_nbr)
		e->sprite_tab[j - 1] = to_free[j];
	e->sprites_nbr--;
	free(to_free);
}

void		apply_damages(t_env *e, int check, int *i)
{
	if (check != -1)
	{
		if (e->sprite_tab[check - 1].life > 0)
			e->sprite_tab[check - 1].life--;
		if (e->sprite_tab[check - 1].life <= 0)
		{
			e->sprite_tab[check - 1].tex_id = 12;
			e->sprite_tab[check - 1].plane_y = 1;
		}
		else
		{
			if (e->sprite_tab[check - 1].plane_x > 0 && !e->vict)
				e->sprite_tab[check - 1].plane_x--;
			else
				e->sprite_tab[check - 1].plane_x = 3;
		}
	}
	remove_one_obj_tab(e, *i);
	*i = *i - 1;
}

int			damage_player(t_env *e, int *i)
{
	if (e->sprite_tab[*i].plane_x != 0
		&& (e->p.pos_x - e->sprite_tab[*i].pos_x)
		* (e->p.pos_x - e->sprite_tab[*i].pos_x)
		+ (e->p.pos_y - e->sprite_tab[*i].pos_y)
		* (e->p.pos_y - e->sprite_tab[*i].pos_y) < 0.1)
	{
		if (e->p.life)
			e->p.life--;
		remove_one_obj_tab(e, *i);
		*i = *i - 1;
		return (1);
	}
	return (0);
}

void		move_bullets(t_env *e)
{
	int		i;
	int		check;

	i = -1;
	while (++i < e->sprites_nbr)
	{
		if (e->sprite_tab[i].tex_id == 13)
		{
			check = colision_check(e, e->sprite_tab[i].pos_x
									+ e->sprite_tab[i].dir_x * 0.5
									, e->sprite_tab[i].pos_y
									+ e->sprite_tab[i].dir_y * 0.5);
			if (check && (check == -1 || e->sprite_tab[i].plane_x == 0))
				apply_damages(e, check, &i);
			else if (!damage_player(e, &i))
			{
				e->sprite_tab[i].pos_x += e->sprite_tab[i].dir_x * 0.5;
				e->sprite_tab[i].pos_y += e->sprite_tab[i].dir_y * 0.5;
			}
		}
	}
}

void		add_one_obj_tab(t_env *e)
{
	int		j;
	t_obj	*to_free;

	j = 0;
	to_free = e->sprite_tab;
	e->sprites_nbr = e->sprites_nbr + 1;
	e->sprite_tab = (t_obj *)malloc(sizeof(t_obj) * e->sprites_nbr);
	while (j < (e->sprites_nbr - 1))
	{
		e->sprite_tab[j] = to_free[j];
		j++;
	}
	free(to_free);
}
