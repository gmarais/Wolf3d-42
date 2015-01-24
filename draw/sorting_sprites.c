/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_colors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/18 17:50:02 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 14:37:54 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		ft_swap_objtab(t_env *e, int *i, int *j)
{
	t_obj	tmpo;

	tmpo = e->sprite_tab[*i];
	e->sprite_tab[*i] = e->sprite_tab[*j];
	e->sprite_tab[*j] = tmpo;
}

void		sort_tab(t_env *e)
{
	int gap;
	int swapped;
	int i;
	int j;

	gap = e->sprites_nbr;
	swapped = 1;
	while (gap > 1 || swapped)
	{
		gap = (gap * 10) / 13;
		gap = (gap == 9 || gap == 10) ? 11 : gap;
		if (gap < 1)
			gap = 1;
		swapped = 0;
		i = -1;
		while (++i < e->sprites_nbr - gap)
		{
			j = i + gap;
			if (e->sprite_tab[i].dist < e->sprite_tab[j].dist)
			{
				ft_swap_objtab(e, &i, &j);
				swapped = 1;
			}
		}
	}
}
