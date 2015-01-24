/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/18 18:18:21 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 20:04:50 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		shoot(t_env *e)
{
	e->shooting = 1;
}

int			key_hook(int keycode, t_env *e)
{
	if (e->p.life)
	{
		if (keycode == 32)
			shoot(e);
		if (keycode == 101)
			apply_teleport(e);
		if (keycode == 65362 || keycode == 122 || keycode == 119)
			e->move.fwd = 1;
		if (keycode == 65364 || keycode == 115)
			e->move.bwd = 1;
		if (keycode == 65361)
			e->move.rlft = 1;
		if (keycode == 65363)
			e->move.rrgt = 1;
		if (keycode == 100)
			e->move.slft = 1;
		if (keycode == 97 || keycode == 113)
			e->move.srgt = 1;
	}
	if (keycode == 65307 && e)
		exit(0);
	return (0);
}

int			key_hook_r(int keycode, t_env *e)
{
	if (keycode == 65362 || keycode == 122 || keycode == 119)
		e->move.fwd = 0;
	if (keycode == 65364 || keycode == 115)
		e->move.bwd = 0;
	if (keycode == 65361)
		e->move.rlft = 0;
	if (keycode == 65363)
		e->move.rrgt = 0;
	if (keycode == 100)
		e->move.slft = 0;
	if (keycode == 97 || keycode == 113)
		e->move.srgt = 0;
	return (0);
}

int			expose_hook(t_env *e)
{
	draw(e);
	return (0);
}
