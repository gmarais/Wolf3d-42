/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 19:33:08 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 20:13:59 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			interface_loader(t_env *e)
{
	text_load(e, &e->gun_tex[0], "./data/xpm_texts/pistolet.xpm");
	text_load(e, &e->gun_tex[1], "./data/xpm_texts/pistolet0.xpm");
	text_load(e, &e->tex_tab[14], "./data/xpm_texts/cookies.xpm");
	text_load(e, &e->tex_tab[15], "./data/xpm_texts/key.xpm");
	text_load(e, &e->tex_tab[16], "./data/xpm_texts/housedoor0.xpm");
	text_load(e, &e->tex_tab[17], "./data/xpm_texts/housewin0.xpm");
	text_load(e, &e->tex_tab[18], "./data/xpm_texts/housewall0.xpm");
	text_load(e, &e->tex_tab[19], "./data/xpm_texts/porte.xpm");
	load_end_screens(e, &e->end_screen[0], "./data/xpm_texts/youdied.xpm");
	load_end_screens(e, &e->end_screen[1], "./data/xpm_texts/youwon.xpm");
	if (!e->gun_tex[0].img || !e->gun_tex[1].img
		|| !e->tex_tab[14].img || !e->tex_tab[15].img
		|| !e->tex_tab[16].img || !e->tex_tab[17].img
		|| !e->tex_tab[18].img || !e->end_screen[0].img
		|| !e->end_screen[1].img || !e->tex_tab[19].img)
		return (-1);
	return (0);
}

int			text_loader(t_env *e)
{
	text_load(e, &e->tex_tab[0], "./data/xpm_texts/trees2.xpm");
	text_load(e, &e->tex_tab[1], "./data/xpm_texts/trees1.xpm");
	text_load(e, &e->tex_tab[2], "./data/xpm_texts/grock.xpm");
	text_load(e, &e->tex_tab[3], "./data/xpm_texts/plank.xpm");
	text_load(e, &e->tex_tab[4], "./data/xpm_texts/housedoor5.xpm");
	text_load(e, &e->tex_tab[5], "./data/xpm_texts/housewall5.xpm");
	text_load(e, &e->tex_tab[6], "./data/xpm_texts/housewin5.xpm");
	text_load(e, &e->tex_tab[7], "./data/xpm_texts/monstblok0.xpm");
	text_load(e, &e->tex_tab[8], "./data/xpm_texts/monstblok.xpm");
	text_load(e, &e->tex_tab[9], "./data/xpm_texts/grass.xpm");
	text_load(e, &e->tex_tab[10], "./data/xpm_texts/monster0.xpm");
	text_load(e, &e->tex_tab[11], "./data/xpm_texts/monster0a.xpm");
	text_load(e, &e->tex_tab[12], "./data/xpm_texts/Monstre0d.xpm");
	text_load(e, &e->tex_tab[13], "./data/xpm_texts/projectile0.xpm");
	load_skybox(e, &e->skybox, "./data/xpm_texts/skybox.xpm");
	if (!e->tex_tab[0].img || !e->tex_tab[1].img
		|| !e->tex_tab[2].img || !e->tex_tab[3].img
		|| !e->tex_tab[4].img || !e->tex_tab[5].img
		|| !e->tex_tab[6].img || !e->tex_tab[7].img
		|| !e->tex_tab[8].img || !e->tex_tab[9].img
		|| !e->tex_tab[10].img || !e->tex_tab[11].img
		|| !e->tex_tab[12].img || !e->tex_tab[13].img
		|| !e->skybox.img)
		return (-1);
	return (0);
}

int			text_load(t_env *e, t_tex *image, char *file)
{
	int		w;
	int		h;

	w = TEX_WIDTH;
	h = TEX_HEIGHT;
	if (!(image->img = mlx_xpm_file_to_image(e->mlx, file, &w, &h)))
		return (-1);
	image->data = mlx_get_data_addr(image->img, &image->bpp,
									&image->sizeline, &image->endian);
	return (0);
}

int			load_skybox(t_env *e, t_tex *image, char *file)
{
	int		w;
	int		h;

	w = SKY_WIDTH;
	h = SKY_HEIGHT;
	if (!(image->img = mlx_xpm_file_to_image(e->mlx, file, &w, &h)))
		return (-1);
	image->data = mlx_get_data_addr(image->img, &image->bpp,
									&image->sizeline, &image->endian);
	return (0);
}

int			load_end_screens(t_env *e, t_tex *image, char *file)
{
	int		w;
	int		h;

	w = 320;
	h = 64;
	if (!(image->img = mlx_xpm_file_to_image(e->mlx, file, &w, &h)))
		return (-1);
	image->data = mlx_get_data_addr(image->img, &image->bpp,
									&image->sizeline, &image->endian);
	return (0);
}
