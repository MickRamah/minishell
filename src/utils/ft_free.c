/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 16:43:04 by zramahaz          #+#    #+#             */
/*   Updated: 2024/11/09 13:23:49 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_env(t_list_env **env)
{
	t_list_env	*tmp;
	t_list_env	*current;

	current = *env;
	if (current == NULL)
		return ;
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
	if (current == NULL)
		return ;
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
	int		i;

	current = *cmd;
	if (current == NULL)
		return ;
	while (current)
	{
		tmp = current->next;
		i = 0;
		free_array(current->argv);
		if (current->infile >= 0)
			close(current->infile);
		current->infile = -2;
		if (current->outfile >= 0)
			close(current->outfile);
		current->outfile = -2;
		free(current);
		current = tmp;
	}
	*cmd = NULL;
}

void	free_data(t_data *data, int ext)
{
	if (data->env != NULL)
		free_env(&data->env);
	if (data->token != NULL)
		free_token(&data->token);
	if (data->cmd != NULL)
		free_cmd(&data->cmd);
	if (!access(TMP_FILE, F_OK))
		unlink(TMP_FILE);
	if (ext != -42)
		exit (ext);
}

void	free_array(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
