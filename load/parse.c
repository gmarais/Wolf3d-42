/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 19:24:28 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 20:12:14 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			numsize(char *str, int i)
{
	int		count;

	count = 0;
	while (str[i] && (str[i] != ' ') && (str[i] != ','))
	{
		count++;
		i++;
	}
	return (count);
}

int			world_init(t_env *e, char *path)
{
	int		fd;
	t_cnt	c;
	char	*line;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (1);
	c.j = -1;
	while (get_next_line(fd, &line) > 0 && line && (c.j++ || 42))
	{
		c.k = 0;
		if (line[(c.i = 0)] && (line[c.i] != ' '))
			world_assign(e, &c, line);
		while (line[c.i] && (line[c.i] == ' '))
		{
			if (line[++(c.i)] && (line[c.i] != ' '))
				world_assign(e, &c, line);
		}
		e->world[c.j][c.k] = NULL;
		free(line);
	}
	e->world[c.j] = NULL;
	close(fd);
	return (0);
}

int			get_world_size(size_t *max_x, size_t *max_y, char *path)
{
	int		fd;
	int		i;
	size_t	maxx;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (1);
	while (get_next_line(fd, &path) > 0 && path)
	{
		i = 0;
		maxx = 0;
		if (path[i] && (path[i] != ' ') && ++maxx)
			i += numsize(path, i);
		while (path[i] && (path[i] == ' '))
		{
			i++;
			if (path[i] && (path[i] != ' ') && ++maxx)
				i += numsize(path, i);
		}
		free(path);
		*max_x = (maxx > *max_x) ? maxx : *max_x;
		(*max_y)++;
	}
	close(fd);
	return (0);
}

int			gather_sprites(t_env *e, char *path)
{
	t_gather	var;

	if (set_sprite_num(e, path, &var))
		return (1);
	if ((var.fd = open(path, O_RDONLY)) < 0)
		return (1);
	var.y = -1;
	while (get_next_line(var.fd, &(var.line)) > 0 && var.line)
	{
		init_sprite_var(e, &var);
		while (var.line[var.x] && var.line[var.x] != ',')
		{
			if (var.line[var.x] == '.' && var.line[var.x + 1]
				&& !var.bol && (var.bol = 1))
				e->sprite_tab[var.y].pos_y = e->sprite_tab[var.y].pos_y
					+ (double)ft_atoi((char *)&(var.line[var.x + 1]))
					/ (double)ft_exp(10, numsize(var.line, var.x + 1));
			var.x++;
		}
		if (var.line[var.x] && var.line[var.x] == ',' && var.line[var.x + 1])
			e->sprite_tab[var.y].tex_id = ft_atoi((char *)&(var.line[var.x
																		+ 1]));
	}
	close(var.fd);
	return (0);
}

void		init_sprite_var(t_env *e, t_gather *var)
{
	var->y++;
	e->sprite_tab[var->y].pos_y = 0.0;
	e->sprite_tab[var->y].plane_y = 0;
	e->sprite_tab[var->y].life = 5;
	e->sprite_tab[var->y].plane_x = var->y % 4;
	e->sprite_tab[var->y].tex_id = 0.0;
	e->sprite_tab[var->y].pos_x = (double)ft_atoi(var->line);
	var->x = 0;
	var->bol = 0;
	while (var->line[var->x] && var->line[var->x] != ',')
	{
		if (var->line[var->x] == '.' && var->line[var->x + 1]
			&& !var->bol && (var->bol = 1))
			e->sprite_tab[var->y].pos_x = e->sprite_tab[var->y].pos_x
				+ (double)(ft_atoi((char *)&(var->line[var->x + 1])))
				/ (ft_exp(10, numsize(var->line, var->x + 1)));
		var->x++;
	}
	if (var->line[var->x] && var->line[var->x] == ',' && var->line[var->x + 1])
		e->sprite_tab[var->y].pos_y = ft_atoi((char *)&(var->line[++var->x]));
	var->bol = 0;
}
