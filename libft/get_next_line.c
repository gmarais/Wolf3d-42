/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/12/02 18:24:37 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 20:25:07 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_ifbufin(char *buf, size_t i)
{
	if (buf[i] == '\n' || buf[i] == '\0')
	{
		ft_strcpy(buf, (char *)&buf[i + 1]);
		buf[ft_strlen(buf) + 1] = '\0';
	}
}

static void	ft_copybuf(char **result, char *buf, size_t *i, size_t *j)
{
	*i = 0;
	while (buf[*i] != '\n' && buf[*i] != '\0' && *i < BUFF_SIZE)
	{
		*result = ft_realloc(*result, ft_strlen(*result) + *j);
		(*result)[*j] = buf[*i];
		(*i)++;
		(*j)++;
	}
	(*result)[*j] = '\0';
}

static int	ft_error(void)
{
	write(2, "Read error.\n", 12);
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	char		*result;
	static char	buf[BUFF_SIZE + 1];
	size_t		i;
	size_t		j;
	ssize_t		ret;

	j = 0;
	result = (char *)malloc(2);
	ft_copybuf(&result, buf, &i, &j);
	ret = ft_strlen(buf) - j;
	while ((buf[i] != '\n') && (ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret < 0 && ft_error())
			return (ret);
		buf[ret] = '\0';
		ft_copybuf(&result, buf, &i, &j);
		i = (i == BUFF_SIZE) ? 0 : i;
	}
	ft_ifbufin(buf, i);
	*line = result;
	if (ret == 0 && ft_strlen(buf) > 0)
		buf[0] = '\0';
	if ((ret > 0 && ret <= BUFF_SIZE) || (ret == 0 && ft_strlen(result) > 0))
		return (1);
	return (0);
}
