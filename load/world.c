/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 19:33:32 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 20:15:25 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		world_assign(t_env *e, t_cnt *c, char *line)
{
	int		count;

	count = numsize(line, c->i);
	e->world[c->j][c->k] = ft_strsub(line, c->i, count);
	(c->k)++;
	c->i += count;
}

int			create_world(t_env *e, char *path)
{
	size_t	max_x;
	size_t	max_y;
	int		error;

	max_x = 0;
	max_y = 0;
	error = get_world_size(&max_x, &max_y, path);
	if (error)
		return (1);
	e->map_width = max_x;
	e->map_height = max_y;
	max_y++;
	max_x++;
	error = world_alloc(e, max_x, max_y);
	if (error)
		return (1);
	error = world_init(e, path);
	if (error)
		return (1);
	return (0);
}

int			set_sprite_num(t_env *e, char *path, t_gather *var)
{
	var->y = 0;
	if ((var->fd = open(path, O_RDONLY)) < 0)
		return (1);
	while (get_next_line(var->fd, &(var->line)) > 0 && var->line)
		var->y++;
	close(var->fd);
	e->sprite_tab = (t_obj *)malloc(sizeof(t_obj) * var->y);
	e->sprites_nbr = var->y;
	return (0);
}

int			world_alloc(t_env *e, int max_x, int max_y)
{
	int		i;

	e->world = (char ***)malloc(max_y * sizeof(char **));
	if (!e->world)
		return (1);
	i = 0;
	while (i < max_y)
	{
		e->world[i] = (char **)malloc(sizeof(char *) * (max_x));
		i++;
	}
	e->world[i] = (char **)malloc(sizeof(char *));
	e->world[i] = NULL;
	return (0);
}
