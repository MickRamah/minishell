/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:58:32 by zramahaz          #+#    #+#             */
/*   Updated: 2024/03/06 11:10:06 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_malloc_error(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static size_t	ft_count_strs(char const *s, char c)
{
	size_t	i;
	size_t	nb_strs;

	i = 0;
	nb_strs = 0;
	if (!s[0])
		return (0);
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
		}
		else
			i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	return (nb_strs);
}

static void	ft_get_next_str(char **next_str, size_t *len, char c)
{
	size_t	i;

	*next_str = *next_str + *len;
	*len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		(*len)++;
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char		**tab;
	char		*next_str;
	size_t		len;
	size_t		i;

	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_count_strs(s, c) + 1));
	if (!tab)
		return (NULL);
	next_str = (char *)s;
	len = 0;
	i = 0;
	while (i < ft_count_strs(s, c))
	{
		ft_get_next_str(&next_str, &len, c);
		tab[i] = ft_substr(next_str, 0, len);
		if (!tab[i])
			return (ft_malloc_error(tab));
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
