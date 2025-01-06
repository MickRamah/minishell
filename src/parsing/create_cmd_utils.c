/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:29:06 by zramahaz          #+#    #+#             */
/*   Updated: 2024/12/23 18:08:48 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_redirection_error(t_token *token, t_data *data)
{
	if (token->next == NULL)
	{
		*(data->exit_code) = 2;
		write(2, "minishell: syntax error near \
		unexpected token `newline'\n", 56);
		return (0);
	}
	else if (token->next && (token->next->type == APPEND || \
		token->next->type == HEREDOC || token->next->type == TRUNC || \
		token->next->type == INPUT || token->next->type == PIPE))
	{
		*(data->exit_code) = 2;
		if (token->next->type == APPEND)
			write(2, \
			"minishell: syntax error near unexpected token `>>'\n", 51);
		else if (token->next->type == HEREDOC)
			write(2, \
			"minishell: syntax error near unexpected token `<<'\n", 51);
		else if (token->next->type == TRUNC)
			write(2, "minishell: syntax error near unexpected token `>'\n", 50);
		else if (token->next->type == INPUT)
			write(2, "minishell: syntax error near unexpected token `<'\n", 50);
		return (0);
	}
	return (1);
}

int	ft_check_error(t_token *begin, t_data *data)
{
	while (begin)
	{
		if (begin->type == APPEND || begin->type == HEREDOC || \
			begin->type == TRUNC || begin->type == INPUT)
		{
			if (check_redirection_error(begin, data) == 0)
				return (1);
			else
				begin = begin->next;
		}
		else if (begin->type == CMD || begin->type == ARG \
			|| begin->type == PIPE)
		{
			if (begin->type == PIPE && begin->next && begin->next->type == PIPE)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				*(data->exit_code) = 2;
				return (1);
			}
			begin = begin->next;
		}
	}
	return (0);
}

static int	create_file(t_cmd *new, t_token **begin, t_data *data)
{
	if ((*begin)->type == APPEND || (*begin)->type == TRUNC)
	{
		if (get_out(new, *begin) == 0)
			return (-1);
	}
	else if ((*begin)->type == INPUT || (*begin)->type == HEREDOC)
	{
		if (get_in(new, *begin, data) == 0)
		{
			if (g_signal_code == -10)
				g_signal_code = 130;
			if (new->infile >= 0)
				close (new->infile);
			return (-1);
		}
	}
	if ((*begin)->next->next == NULL)
		(*begin) = (*begin)->next->next;
	else
		(*begin) = (*begin)->next->next;
	return (1);
}

int	add_to_cmd(t_cmd *new, t_token **begin, t_data *data)
{
	int	i;

	i = 0;
	while (*begin && (*begin)->type != PIPE)
	{
		new->argv[i] = NULL;
		if ((*begin)->type == APPEND || (*begin)->type == HEREDOC || \
			(*begin)->type == TRUNC || (*begin)->type == INPUT)
		{
			if (create_file(new, begin, data) == -1)
				return (-1);
		}
		else if ((*begin)->type == CMD || (*begin)->type == ARG)
		{
			new->argv[i] = ft_strdup((*begin)->str);
			if (new->argv[i] == NULL)
				return (0);
			*begin = (*begin)->next;
			i++;
		}
	}
	new->argv[i] = NULL;
	return (1);
}
