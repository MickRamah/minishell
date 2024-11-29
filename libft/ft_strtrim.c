/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:39:31 by zramahaz          #+#    #+#             */
/*   Updated: 2024/03/02 11:36:18 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, char const *set)
{
	size_t	last;

	if (s == NULL || set == NULL)
		return (NULL);
	while (*s && ft_strchr(set, *s))
		s++;
	last = ft_strlen(s);
	while (last && ft_strrchr(set, s[last]))
		last--;
	return (ft_substr(s, 0, last + 1));
}
