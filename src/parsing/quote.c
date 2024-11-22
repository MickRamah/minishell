/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:27:33 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/11 16:22:51 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_quote(char c, bool *dq, bool *sq)
{
	if (c == '\'' && !(*sq) && (*dq) == false)
		(*sq) = true;
	else if (c == '\'' && (*sq) && (*dq) == false)
		(*sq) = false;
	if (c == '"' && (*dq) == false && (*sq) == false)
		(*dq) = true;
	else if (c == '"' && (*dq) == true && (*sq) == false)
		(*dq) = false;
}

static int	close_quote(char *line, int *i_ptr, char c)
{
	int	i;

	i = *i_ptr;
	if (c == '\'')
	{
		while (line[i++])
		{
			if (line[i] == '\'')
			{
				*i_ptr = i;
				return (1);
			}
		}
		return (0);
	}
	while (line[i++])
	{
		if (line[i] == '"')
		{
			*i_ptr = i;
			return (1);
		}
	}
	return (0);
}

int	check_quote(t_data *data, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !close_quote(line, &i, '\''))
		{
			write(2, "quote is open\n", 14);
			data->exit_code = 2;
			return (0);
		}
		else if (line[i] == '"' && !close_quote(line, &i, '"'))
		{
			write(2, "quote is open\n", 14);
			data->exit_code = 2;
			return (0);
		}
		i++;
	}
	return (1);
}
