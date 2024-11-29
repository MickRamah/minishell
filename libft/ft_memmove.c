/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 16:10:25 by zramahaz          #+#    #+#             */
/*   Updated: 2024/02/28 15:26:44 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *d, const void *s, size_t size)
{
	size_t	i;

	if (!d && !s)
		return (NULL);
	i = 0;
	if (d < s)
	{
		while (i < size)
		{
			*(unsigned char *)(d + i) = *(unsigned char *)(s + i);
			i++;
		}
	}
	else
		while (size--)
			*(unsigned char *)(d + size) = *(unsigned char *)(s + size);
	return (d);
}
