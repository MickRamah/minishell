/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:31:55 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/11 16:17:41 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_char(char c, char **str)
{
	char	*tmp;
	char	tab[2];

	tab[0] = c;
	tab[1] = 0;
	tmp = ft_strjoin(*str, tab);
	free(*str);
	if (tmp == NULL)
		exit (1);
	*str = tmp;
}

int	add_dollar(char *line, char **str, int *index, t_list_env *env)
{
	if (exist_in_env(line, env, index, str))
		return (1);
	while (line[*index] && (line[*index] != ' ' && line[*index] != '"'))
		(*index)++;
}

int	replace_dollar(char **line, t_data *data)
{
	int		i;
	char	*str;

	i = 0;
	data->sq = false;
	str = malloc(sizeof(char));
	if (str == NULL)
		exit (1);
	*str = '\0';
	while (line[0][i])
	{
		if (line[0][i] == '\'' && !data->sq)
			data->sq = true;
		else if (line[0][i] == '\'' && data->sq)
			data->sq = false;
		if (line[0][i] == '$' && isalpha(line[0][i + 1]) && !data->sq)
			add_dollar(line[0], &str, &i, data->env);
		else if (line[0][i])
		{
			add_char(line[0][i], &str);
			i++;
		}
	}
	*line = str;
	return (1);
}
