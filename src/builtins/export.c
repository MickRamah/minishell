/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 17:14:07 by herakoto          #+#    #+#             */
/*   Updated: 2024/11/21 17:36:47 by zramahaz         ###   ########.fr       */
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
	int			i;
	int			j;
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
		{
			if (ft_is_void(str) == 1)
				return (j);
			return (-2);
		}
		tmp = tmp->next;
		j++;
	}
	return (-1);
}

bool	export(char *str, t_list_env **env)
{
	int			pos;
	int			i;
	char		*value;
	t_list_env	*tmp;

	pos = ft_exist(str, (*env));
	if (pos == -2)
		return (true);
	value = ft_strdup(str);
	if (!value)
		return (false);
	if (pos >= 0)
	{
		tmp = *env;
		i = 0;
		while (i++ < pos)
			tmp = tmp->next;
		free(tmp->str);
		tmp->str = value;
	}
	else if (pos == -1)
		if (!append_in_env(env, value))
			return (false);
	return (true);
}

int	ft_export(char **str, t_list_env **env)
{
	int	i;
	int	exit_code;
	int	count;

	i = 1;
	exit_code = 0;
	count = count_arg(str);
	if (count == 1)
		return (ft_export_no_args(*env));
	count = count_arg(str);
	while (i < count)
	{
		if (!valid_identifier(str[i]))
		{
			write(2, "export: invalid identifier\n", 27);
			exit_code = 1;
		}
		else if (!export(str[i], env))
			return (write(2, "malloc error\n", 13));
		i++;
	}
	return (exit_code);
}
