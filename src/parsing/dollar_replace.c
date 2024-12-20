/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:31:55 by zramahaz          #+#    #+#             */
/*   Updated: 2024/11/09 13:45:00 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	add_char(char c, char **str)
{
	char	*tmp;
	char	tab[2];

	tab[0] = c;
	tab[1] = 0;
	tmp = ft_strjoin(*str, tab);
	free(*str);
	if (tmp == NULL)
		return (0);
	*str = tmp;
	return (1);
}

static int	dollar_point_interrogation(t_data *data, char **str)
{
	char	*tmp;
	char	*tmp2;

	tmp = ft_itoa(*(data->exit_code));
	if (!tmp)
		return (0);
	tmp2 = ft_strjoin(*str, tmp);
	free(tmp);
	free(*str);
	if (!tmp2)
		return (0);
	*str = tmp2;
	return (1);
}

static int	add_dollar(t_data *data, char *line, char **str, int *index)
{
	int			status;
	t_list_env	*env;

	env = data->env;
	status = exist_in_env(line, env, index, str);
	if (status == -1)
		return (0);
	else if (status == 1)
		return (1);
	if (status == 2)
	{
		(*index) += 2;
		dollar_point_interrogation(data, str);
		return (1);
	}
	(*index)++;
	while (line[*index] && line[*index] != '$' && \
		(line[*index] != ' ' && line[*index] != '"'))
		(*index)++;
	return (1);
}

static int	check_heredoc(char *line, int i)
{
	int	nb;

	nb = i - 1;
	while (nb >= 0 && line[nb] && is_space(line[nb]))
		nb--;
	if (nb >= 1 && line[nb - 1] == '<' && line[nb] == '<')
		return (1);
	return (0);
}

int	replace_dollar(char **line, t_data *data, int i)
{
	char	*str;

	str = ft_strdup("");
	if (str == NULL)
		return (0);
	while (line[0][i])
	{
		change_quote(line[0][i], &(data->dq), &(data->sq));
		if (check_heredoc(line[0], i))
			while (line[0][i] && !is_space(line[0][i]))
				add_char(line[0][i++], &str);
		if (line[0][i] == '$' && (isalpha(line[0][i + 1]) || \
			line[0][i + 1] == '?' || line[0][i + 1] == '"' || \
			line[0][i + 1] == '\'') && (!data->sq || data->dq))
		{
			if (add_dollar(data, line[0], &str, &i) == 0)
				return (0);
		}
		else if (line[0][i] && add_char(line[0][i++], &str) == 0)
			return (0);
	}
	free(*line);
	*line = str;
	return (1);
}
