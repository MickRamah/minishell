/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:00:30 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/15 14:04:21 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static char	*ft_strcpy(char *dest, char const *src)
// {
// 	int	i;

// 	i = -1;
// 	while (src[++i] != '\0')
// 		dest[i] = src[i];
// 	dest[i] = '\0';
// 	return (dest);
// }

// static char	*ft_strcat(char *dest, char const *src)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (dest[i])
// 		i++;
// 	j = -1;
// 	while (src[++j])
// 		dest[i++] = src[j];
// 	dest[i] = '\0';
// 	return (dest);
// }

// char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	char	*dest;
// 	size_t	len;

// 	len = ft_strlen(s1);
// 	len += ft_strlen(s2);
// 	dest = (char *)malloc(len + 1);
// 	if (!dest)
// 		return (NULL);
// 	ft_strcpy(dest, s1);
// 	ft_strcat(dest, s2);
// 	return (dest);
// }

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++j])
		str[++i] = s1[j];
	j = -1;
	while (s2[++j])
		str[++i] = s2[j];
	str[i + 1] = '\0';
	return (str);
}
