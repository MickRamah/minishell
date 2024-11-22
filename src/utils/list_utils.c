/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:54:27 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/14 10:25:52 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list_env	*ft_last_list_env(t_list_env *list)
{
	t_list_env	*last;

	last = list;
	while (last->next)
		last = last->next;
	return (last);
}

t_token	*ft_last_list_token(t_token *list)
{
	t_token	*last;

	last = list;
	if (last == NULL)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

t_cmd	*ft_last_list_cmd(t_cmd *command)
{
	t_cmd	*last;

	last = command;
	if (last == NULL)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

int	append_in_env(t_list_env **list, char *line)
{
	t_list_env	*new;
	t_list_env	*last;

	new = (t_list_env *)malloc(sizeof(t_list_env));
	if (new == NULL)
		return (0);
	new->next = NULL;
	new->prev = NULL;
	new->str = line;
	if (*list == NULL)
		*list = new;
	else
	{
		last = ft_last_list_env(*list);
		last->next = new;
		new->prev = last;
	}
	return (1);
}
