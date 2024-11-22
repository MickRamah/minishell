/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 13:35:46 by zramahaz          #+#    #+#             */
/*   Updated: 2024/11/09 13:56:24 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	get_nbrs_cmd(t_token *begin)
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

static t_cmd	*create_and_init_cmd(int nb)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->infile = -2;
	new->outfile = -2;
	new->argv = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!new->argv)
	{
		free(new);
		return (NULL);
	}
	return (new);
}

static int	append_cmd(t_cmd **command, t_token **begin, int nb, t_data *data)
{
	t_cmd	*new;
	t_cmd	*last;
	int		status;

	new = create_and_init_cmd(nb);
	if (new == NULL)
		return (0);
	status = add_to_cmd(new, begin, data);
	if (status == -1 || status == 0)
	{
		free_cmd(&new);
		if (status == -1)
			return (-1);
		else
			return (0);
	}
	if (*command == NULL)
	{
		*command = new;
		return (1);
	}
	last = ft_last_list_cmd(*command);
	last->next = new;
	new->prev = last;
	return (1);
}

int	create_list_cmd(t_data *data)
{
	t_token	*begin;
	int		nb;
	int		status;

	nb = 0;
	begin = data->token;
	if (ft_check_error(begin, data))
		return (0);
	while (begin)
	{
		nb = get_nbrs_cmd(begin);
		if (nb == -1)
			return (0);
		status = append_cmd(&data->cmd, &begin, nb, data);
		if (status == -1)
		{
			data->exit_code = 2;
			return (0);
		}
		if (status == 0)
			free_data(data, 1);
		if (begin && begin->type == PIPE)
			begin = begin->next;
	}
	return (1);
}
