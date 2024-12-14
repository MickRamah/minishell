/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:02:56 by zramahaz          #+#    #+#             */
/*   Updated: 2024/11/09 13:53:59 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	append_in_token(t_token **begin, char *line, int type)
{
	t_token	*new;
	t_token	*last;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (0);
	new->next = NULL;
	new->type = type;
	new->quote = false;
	new->str = ft_strdup(line);
	free(line);
	if (new->str == NULL)
		return (0);
	if (*begin == NULL)
	{
		*begin = new;
		new->prev = NULL;
		return (1);
	}
	last = ft_last_list_token(*begin);
	last->next = new;
	new->prev = last;
	return (1);
}

static void	change_str(char *command, char *tmp, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (command[i + j] && i < size)
	{
		if (command[i + j] == '"' && ++j)
		{
			while (command[i + j] != '"' && ++i)
				tmp[i - 1] = command[i + j - 1];
			j++;
		}
		else if (command[i + j] == '\'' && ++j)
		{
			while (command[i + j] != '\'' && ++i)
				tmp[i - 1] = command[i + j - 1];
			j++;
		}
		else
		{
			tmp[i] = command[i + j];
			i++;
		}
	}
}

static void	len_cmd(char *command, int *quote, int *lenght)
{
	while (command[*lenght] && command[*lenght] != ' ' \
		&& !is_special(command + (*lenght)))
	{
		if (command[*lenght] == '"')
		{
			(*quote)++;
			(*lenght)++;
			while (command[*lenght] && command[*lenght] != '"')
				(*lenght)++;
			(*quote)++;
		}
		else if (command[*lenght] == '\'')
		{
			(*quote)++;
			(*lenght)++;
			while (command[*lenght] && command[*lenght] != '\'')
				(*lenght)++;
			(*quote)++;
		}
		if (command[*lenght])
			(*lenght)++;
		if (command[*lenght] && command[*lenght] != ' ' \
			&& command[*lenght] != '"' && command[*lenght] != '\'')
			(*lenght)++;
	}
}

static int	add_cmd(t_token **begin, char **command)
{
	int		lenght;
	int		quote;
	char	*tmp;
	t_token	*last;

	quote = 0;
	lenght = 0;
	len_cmd(*command, &quote, &lenght);
	tmp = (char *)malloc(sizeof(char) * (lenght - quote + 1));
	if (tmp == NULL)
		return (0);
	change_str(*command, tmp, lenght - quote);
	tmp[lenght - quote] = 0;
	if (append_in_token(begin, tmp, 0) == 0)
		return (0);
	last = ft_last_list_token(*begin);
	if (quote)
		last->quote = true;
	if (last->prev == NULL || last->prev->type == PIPE)
		last->type = CMD;
	else
		last->type = ARG;
	(*command) += lenght;
	return (1);
}

int	create_list_token(t_token **begin, char *line)
{
	while (*line)
	{
		line += ft_strspn(line, " ");
		if (is_special(line))
		{
			if (add_special(begin, &line) == 0)
			{
				return (0);
			}
		}
		else if (*line && !is_space(*line))
		{
			if (add_cmd(begin, &line) == 0)
				return (0);
		}
	}
	return (1);
}
