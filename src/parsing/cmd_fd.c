/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:10:29 by zramahaz          #+#    #+#             */
/*   Updated: 2024/12/23 15:38:54 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_check_fd(char *var)
{
	if (errno == ENOENT)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(" : no such file or directory\n", 2);
		return (0);
	}
	else if (errno == EACCES)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(" : permissin denied\n", 2);
		return (0);
	}
	return (0);
}

int	get_out(t_cmd *command, t_token *token)
{
	if (token->type == TRUNC)
	{
		if (command->outfile >= 0)
			close(command->outfile);
		command->outfile = open(token->next->str, O_CREAT | O_WRONLY | \
					O_TRUNC, 0644);
		if (command->outfile == -1)
		{
			g_signal_code = 2;
			return (ft_check_fd(token->next->str));
		}
	}
	else if (token->type == APPEND)
	{
		if (command->outfile >= 0)
			close(command->outfile);
		command->outfile = open(token->next->str, O_CREAT | O_WRONLY | \
					O_APPEND, 0644);
		if (command->outfile == -1)
		{
			g_signal_code = 2;
			return (ft_check_fd(token->next->str));
		}
	}
	return (1);
}

int	get_in(t_cmd *command, t_token *token, t_data *data)
{
	if (token->type == INPUT)
	{
		if (command->infile >= 0)
			close(command->infile);
		command->infile = open(token->next->str, O_RDONLY, 0644);
		if (command->infile == -1)
		{
			g_signal_code = 1;
			return (ft_check_fd(token->next->str));
		}
	}
	else if (token->type == HEREDOC)
	{
		if (command->infile >= 0)
			close(command->infile);
		command->infile = here_doc(token->next->str, data, token->next->quote);
		if (command->infile == -1)
		{
			g_signal_code = 2;
			return (0);
		}
		if (g_signal_code == -10)
			return (0);
	}
	return (1);
}
