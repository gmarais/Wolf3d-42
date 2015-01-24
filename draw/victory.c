/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/18 18:16:56 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/20 16:03:59 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		check_victory(t_env *e)
{
	int			i;
	int			win;

	i = -1;
	win = 1;
	while (++i < e->sprites_nbr)
	{
		if (e->sprite_tab[i].tex_id == 10
			|| e->sprite_tab[i].tex_id == 11
			|| e->sprite_tab[i].tex_id == 12)
		{
			if (e->sprite_tab[i].plane_x != 3)
				win = 0;
		}
	}
	if (win)
	{
		e->p.life = 100;
		e->vict = 1;
		end_to_img(e);
	}
}
