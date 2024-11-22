/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 17:06:29 by zramahaz          #+#    #+#             */
/*   Updated: 2024/02/28 16:42:16 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t size)
{
	int			i;
	int			pos;
	const char	*dest;

	dest = s;
	pos = -1;
	i = -1;
	while (size-- && pos == -1)
		if (dest[++i] == (char)c)
			pos = i;
	if (pos == -1)
		return (NULL);
	s = s + pos;
	return ((void *)s);
}
