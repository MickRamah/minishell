/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 10:10:29 by zramahaz          #+#    #+#             */
/*   Updated: 2024/11/09 13:59:09 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	get_out(t_cmd *command, t_token *token)
{
	if (token->type == TRUNC)
	{
		if (command->outfile >= 0)
			close(command->outfile);
		command->outfile = open(token->next->str, O_CREAT | O_WRONLY | \
					O_TRUNC, 0644);
		if (command->outfile == -1)
			return (0);
	}
	else if (token->type == APPEND)
	{
		command->outfile = open(token->next->str, O_CREAT | O_WRONLY | \
					O_APPEND, 0644);
		if (command->outfile == -1)
			return (0);
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
			return (0);
	}
	else if (token->type == HEREDOC)
	{
		if (command->infile >= 0)
			close(command->infile);
		command->infile = here_doc(token->next->str, data, token->next->quote);
		if (command->infile == -1)
			return (0);
	}
	return (1);
}
