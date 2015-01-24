/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/27 13:07:14 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 20:21:28 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *s, size_t n)
{
	void	*copy;

	copy = malloc(n);
	if (s != NULL)
	{
		copy = ft_memcpy(copy, s, n);
		free(s);
	}
	return (copy);
}
