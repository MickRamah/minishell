/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:35:46 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/11 15:58:02 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_error(t_token *begin)
{
	while (begin)
	{
		if (begin->type == APPEND || begin->type == HEREDOC || \
			begin->type == TRUNC || begin->type == INPUT)
		{
			if (begin->next == NULL)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (1);
			}
			else if (begin->next && (begin->next->type == APPEND || \
				begin->next->type == HEREDOC || begin->next->type == TRUNC || \
				begin->next->type == INPUT) || begin->next->type == PIPE)
			{
				printf("minishell: syntax error near unexpected token `...'\n");
				return (1);
			}
			else
				begin = begin->next;
		}
		else if (begin->type == CMD || begin->type == ARG || begin->type == PIPE)
		{
			if (begin->type == PIPE && begin->next && begin->next->type == PIPE)
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
			begin = begin->next;
		}
	}
	return (0);
}

int	get_nbrs_cmd(t_token *begin)
{
	int	count;

	count = 0;
	while (begin && begin->type != PIPE)
	{
		if (begin->type == CMD || begin->type == ARG)
		{
			count++;
			begin = begin->next;
		}
		else if (begin->type == APPEND || begin->type == HEREDOC || \
			begin->type == TRUNC || begin->type == INPUT)
		{
			if (begin->next->next == NULL)
				return (count);
			else if (begin->next->next && (begin->next->next->type == CMD || \
				begin->next->next->type == ARG))
				begin = begin->next->next;
			else
				begin = begin->next->next;
		}
	}
	return (count);
}

void	add_to_cmd(t_cmd *new, t_token **begin)
{
	int	i;

	i = 0;
	while (*begin && (*begin)->type != PIPE)
	{
		if ((*begin)->type == APPEND || (*begin)->type == HEREDOC || \
			(*begin)->type == TRUNC || (*begin)->type == INPUT)
		{
			if ((*begin)->next->next == NULL)
				(*begin) = (*begin)->next->next;
			else
			{
				(*begin) = (*begin)->next->next;
			}
		}
		else if ((*begin)->type == CMD || (*begin)->type == ARG)
		{
			new->argv[i] = ft_strdup((*begin)->str);
			*begin = (*begin)->next;
			i++;
		}
	}
}

void	append_cmd(t_cmd **command, t_token **begin, int nb)
{
	t_cmd	*new;
	t_cmd	*last;
	int		i;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		exit (1);
	new->next = NULL;
	new->argv = (char **)malloc(sizeof(char *) * (nb + 1));
	new->argv[nb] = NULL;
	if (!new->argv)
		exit (1);
	add_to_cmd(new, begin);
	if (*command == NULL)
	{
		*command = new;
		new->prev = NULL;
		return ;
	}
	last = ft_last_list_cmd(*command);
	last->next = new;
	new->prev = last;
}

int	create_list_cmd(t_data *data)
{
	t_token	*begin;
	int		nb;

	nb = 0;
	begin = data->token;
	if (ft_check_error(begin))
		return (1);
	while (begin)
	{
		nb = get_nbrs_cmd(begin);
		if (nb == -1)
			return (0);
		append_cmd(&data->cmd, &begin, nb);
		if (begin && begin->type == PIPE)
			begin = begin->next;
	}
	return (1);
}
