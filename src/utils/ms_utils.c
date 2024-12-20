/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:18:35 by zramahaz          #+#    #+#             */
/*   Updated: 2024/11/09 13:24:53 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t' \
		|| c == '\v'))
		return (true);
	return (false);
}

int	is_special(char *command)
{
	int	len;

	len = ft_strlen(command);
	if (len >= 2)
	{
		if (ft_strncmp(command, ">>", 2) == 0)
			return (APPEND);
		if (ft_strncmp(command, "<<", 2) == 0)
			return (HEREDOC);
	}
	if (len >= 1)
	{
		if (ft_strncmp(command, "|", 1) == 0)
			return (PIPE);
		if (ft_strncmp(command, ">", 1) == 0)
			return (TRUNC);
		if (ft_strncmp(command, "<", 1) == 0)
			return (INPUT);
	}
	return (0);
}

int	add_special(t_token **begin, char **command)
{
	int	val;

	val = is_special(*command);
	if (val == APPEND)
		if (append_in_token(begin, ft_strdup(">>"), APPEND) == 0)
			return (0);
	if (val == HEREDOC)
		if (append_in_token(begin, ft_strdup("<<"), HEREDOC) == 0)
			return (0);
	if (val == TRUNC)
		if (append_in_token(begin, ft_strdup(">"), TRUNC) == 0)
			return (0);
	if (val == INPUT)
		if (append_in_token(begin, ft_strdup("<"), INPUT) == 0)
			return (0);
	if (val == PIPE)
		if (append_in_token(begin, ft_strdup("|"), PIPE) == 0)
			return (0);
	if (val == APPEND || val == HEREDOC)
		(*command) += 2;
	else if (val == TRUNC || val == INPUT || val == PIPE)
		(*command)++;
	return (1);
}

size_t	ft_strspn(const char *s, const char *accept)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	while (s[i])
	{
		j = 0;
		check = 0;
		while (accept[j])
		{
			if (s[i] == accept[j])
				check = 1;
			j++;
		}
		if (check == 0)
			return (i);
		i++;
	}
	return (i);
}

int	check_pipe(t_data *data, t_token *token)
{
	t_token	*last;

	last = ft_last_list_token(token);
	if (token && token->type == PIPE)
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 51);
		*(data->exit_code) = 2;
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (0);
	}
	if (last && last->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		*(data->exit_code) = 2;
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (0);
	}
	return (1);
}
