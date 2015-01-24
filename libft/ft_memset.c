/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmarais <gmarais@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 11:40:26 by gmarais           #+#    #+#             */
/*   Updated: 2015/01/22 20:20:41 by gmarais          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	letter;
	unsigned char	*str;

	str = (unsigned char*)b;
	letter = (unsigned char)c;
	while (len)
	{
		len--;
		str[len] = letter;
	}
	return (b);
}
