/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:43:04 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/11 16:28:24 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env(t_list_env **env)
{
	t_list_env	*tmp;
	t_list_env	*current;

	current = *env;
	while (current)
	{
		tmp = current->next;
		free(current->str);
		free(current);
		current = tmp;
	}
	*env = NULL;
}

void	free_token(t_token **token)
{
	t_token	*tmp;
	t_token	*current;

	current = *token;
	while (current)
	{
		tmp = current->next;
		free(current->str);
		free(current);
		current = tmp;
	}
	*token = NULL;
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*tmp;
	t_cmd	*current;

	current = *cmd;
	while (current)
	{
		tmp = current->next;
		free(current);
		current = tmp;
	}
	*cmd = NULL;
}
