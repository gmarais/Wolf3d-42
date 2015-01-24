/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/01/18 17:50:48 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 20:02:35 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		sprite_casting(t_env *e, t_trac_data *d)
{
	t_spricast	va;

	showgun(e);
	init_sprite_tab(e);
	sort_tab(e);
	va.i = -1;
	while (++(va.i) < e->sprites_nbr)
	{
		set_trans_xy(e, &va);
		set_sprite_draw_strt_nd(&va, d, e);
		d->x = d->draw_start - 1;
		while (++(d->x) < d->draw_end)
			print_my_sprite(e, d, &va);
	}
	gun_to_img(e);
}

void		init_sprite_tab(t_env *e)
{
	static int	ct = 0;
	int			i;

	ct++;
	i = -1;
	while (++i < e->sprites_nbr)
	{
		if (ct == 20 && e->sprite_tab[i].tex_id == 10)
			e->sprite_tab[i].tex_id = 11;
		else if (ct == 20 && e->sprite_tab[i].tex_id == 11)
			e->sprite_tab[i].tex_id = 10;
		e->sprite_tab[i].dist = ((e->p.pos_x - e->sprite_tab[i].pos_x)
						* (e->p.pos_x - e->sprite_tab[i].pos_x)
						+ (e->p.pos_y - e->sprite_tab[i].pos_y)
						* (e->p.pos_y - e->sprite_tab[i].pos_y));
	}
	if (ct >= 20)
		ct = 0;
}

void		set_trans_xy(t_env *e, t_spricast *va)
{
	double	rel_spt_x;
	double	rel_spt_y;
	double	inv_det;

	rel_spt_x = (e->sprite_tab[va->i]).pos_x - e->p.pos_x;
	rel_spt_y = (e->sprite_tab[va->i]).pos_y - e->p.pos_y;
	inv_det = 1.0 / (e->p.plane_x * e->p.dir_y
						- e->p.plane_y * e->p.dir_x);
	va->trans_x = inv_det * (e->p.dir_y * rel_spt_x
								- e->p.dir_x * rel_spt_y);
	va->trans_y = inv_det * (-(e->p.plane_y) * rel_spt_x
								+ e->p.plane_x * rel_spt_y);
}

void		set_sprite_draw_strt_nd(t_spricast *va, t_trac_data *d, t_env *e)
{
	int		z_mv;

	z_mv = (e->sprite_tab[va->i].tex_id >= 14) ? 20 : 0;
	va->sprite_screen_x = (int)((SCREEN_WIDTH / 2)
								* (1 + va->trans_x / va->trans_y));
	va->sprite_height = ft_abs((int)(SCREEN_HEIGHT / va->trans_y));
	if (e->sprite_tab[va->i].tex_id == 14)
		va->sprite_height /= 2;
	va->draw_start_y = SCREEN_HEIGHT / 2 + z_mv - va->sprite_height / 2;
	if (va->draw_start_y < 0)
		va->draw_start_y = 0;
	va->draw_end_y = SCREEN_HEIGHT / 2 + z_mv + va->sprite_height / 2;
	if (va->draw_end_y >= SCREEN_HEIGHT)
		va->draw_end_y = SCREEN_HEIGHT - 1;
	va->sprite_width = ft_abs((int)(SCREEN_HEIGHT / (va->trans_y)));
	d->draw_start = va->sprite_screen_x - va->sprite_width / 2;
	if (d->draw_start < 0)
		d->draw_start = 0;
	d->draw_end = va->sprite_screen_x + va->sprite_width / 2;
	if (d->draw_end >= SCREEN_WIDTH)
		d->draw_end = SCREEN_WIDTH - 1;
}
