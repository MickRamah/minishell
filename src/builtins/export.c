/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:14:07 by herakoto          #+#    #+#             */
/*   Updated: 2024/11/26 18:01:13 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_export_no_args(t_list_env *env)
{
	t_list_env	*tmp;
	int			j;

	tmp = env;
	while (tmp != NULL)
	{
		printf("declare -x ");
		j = 0;
		while ((tmp->str)[j] && (tmp->str)[j] != '=')
			printf("%c", (tmp->str)[j++]);
		if ((tmp->str)[j] && (tmp->str)[j] == '=')
			printf("=\"%s\"\n", &(tmp->str)[j + 1]);
		else
			printf("\n");
		tmp = tmp->next;
	}
	return (0);
}

static bool	valid_identifier(char *str)
{
	int	i;

	i = 0;
	if (!str[0] || (str[0] != '_' && !ft_isalpha(str[0])))
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

static int	ft_exist(char *str, t_list_env *env)
{
	int		i;
	int		j;
	t_list_env	*tmp;

	if (!env)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	j = 0;
	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->str, str, i) == 0
			&& (tmp->str[i] == '\0' || tmp->str[i] == '='))
			return (j);
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

bool	export(char *str, t_list_env **env)
{
	int		pos;
	int		i;
	char	*value;
	t_list_env	*tmp;

	pos = ft_exist(str, (*env));
	value = ft_strdup(str);
	if (!value)
		return (false);
	if (pos >= 0)
	{
		tmp = *env;
		i = 0;
		while (i < pos)
		{
			tmp = tmp->next;
			i++;
		}
		free(tmp->str);
		tmp->str = value;
	}
	else if (pos == -1)
	{
		if (!append(env, value))
			return (false);
	}
	return (true);
}

int	ft_export(char **str, t_list_env **env)
{
	int	i;
	int	count;

	i = 1;
	if (ft_count_arg(str) == 1)
		return (ft_export_no_args(*env));
	count = ft_count_arg(str);
	while (i < count)
	{
		export(str[i], env);
		i++;
	}
	return (1);
}
