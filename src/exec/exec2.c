/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:46:03 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/17 10:47:39 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**ft_get_all_path(t_list_env *env)
{
	char		*path;
	char		**all_path;
	t_list_env	*current;

	path = NULL;
	all_path = NULL;
	current = env;
	while (current)
	{
		if (ft_strncmp(current->str, "PATH", 4) == 0)
		{
			path = current->str + 5;
			all_path = ft_split(path, ':');
			return (all_path);
		}
		current = current->next;
	}
	return (NULL);
}
