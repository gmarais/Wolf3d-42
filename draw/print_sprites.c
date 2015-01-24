/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_cast2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/18 17:58:01 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 20:01:49 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		print_my_sprite(t_env *e, t_trac_data *d, t_spricast *va)
{
	d->tex_x = (int)(256 * (d->x - (va->sprite_screen_x - va->sprite_width / 2))
						* TEX_WIDTH / va->sprite_width) / 256;
	if (va->trans_y > 0 && d->x > 0 && d->x < SCREEN_WIDTH
		&& va->trans_y < d->z_buffer[d->x])
	{
		va->y = va->draw_start_y - 1;
		while (++(va->y) < va->draw_end_y)
		{
			pimp_my_sprite(e, d, va);
			if (va->col.b || va->col.g || va->col.r)
				sprite_in_img(e, d, va);
		}
	}
}

void		pimp_my_sprite(t_env *e, t_trac_data *d, t_spricast *va)
{
	int		z_mv;
	int		dec;
	int		id;

	z_mv = (e->sprite_tab[va->i].tex_id >= 14) ? 20 : 0;
	id = (e->sprite_tab[va->i]).tex_id;
	dec = (va->y - z_mv) * 256 - SCREEN_HEIGHT * 128 + va->sprite_height * 128;
	d->tex_y = ((dec * TEX_HEIGHT) / va->sprite_height) / 256;
	va->col.b = ((e->tex_tab[id]).data)[(d->tex_y
											* (e->tex_tab[id]).sizeline
											+ ((e->tex_tab[id]).bpp / 8)
											* d->tex_x)];
	va->col.g = ((e->tex_tab[id]).data)[(d->tex_y
											* (e->tex_tab[id]).sizeline
											+ ((e->tex_tab[id]).bpp / 8)
											* d->tex_x) + 1];
	va->col.r = ((e->tex_tab[id]).data)[(d->tex_y
											* (e->tex_tab[id]).sizeline
											+ ((e->tex_tab[id]).bpp / 8)
											* d->tex_x) + 2];
}

void		sprite_in_img(t_env *e, t_trac_data *d, t_spricast *va)
{
	if (!(e->sprite_tab[va->i]).plane_x)
	{
		e->data[va->y * e->sizeline + d->x * (e->bpp / 8)] = va->col.b;
		e->data[va->y * e->sizeline + d->x * (e->bpp / 8) + 1] = va->col.g;
		e->data[va->y * e->sizeline + d->x * (e->bpp / 8) + 2] = va->col.r;
	}
	else if ((e->sprite_tab[va->i]).plane_x == 1)
	{
		e->data[va->y * e->sizeline + d->x * (e->bpp / 8)] = va->col.r;
		e->data[va->y * e->sizeline + d->x * (e->bpp / 8) + 1] = va->col.b;
		e->data[va->y * e->sizeline + d->x * (e->bpp / 8) + 2] = va->col.g;
	}
	else if ((e->sprite_tab[va->i]).plane_x == 2)
	{
		e->data[va->y * e->sizeline + d->x * (e->bpp / 8)] = va->col.b;
		e->data[va->y * e->sizeline + d->x * (e->bpp / 8) + 1] = va->col.r;
		e->data[va->y * e->sizeline + d->x * (e->bpp / 8) + 2] = va->col.g;
	}
	else
	{
		e->data[va->y * e->sizeline + d->x * (e->bpp / 8)] = va->col.r;
		e->data[va->y * e->sizeline + d->x * (e->bpp / 8) + 1] = va->col.g;
		e->data[va->y * e->sizeline + d->x * (e->bpp / 8) + 2] = va->col.b;
	}
}
