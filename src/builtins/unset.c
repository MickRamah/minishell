/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:54:32 by herakoto          #+#    #+#             */
/*   Updated: 2024/11/21 17:37:54 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_strcmp_export(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && (s1[i] == s2[i]))
	{
		if (s2[i + 1] == '=' && ft_strlen_export(s1) == ft_strlen_export(s2))
			return (0);
		else if (s2[i + 1] == '\0'
			&& ft_strlen_export(s1) == ft_strlen_export(s2))
			return (0);
		i++;
	}
	return (1);
}

int	ft_isequal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static t_list_env	*ft_exist(char *var, t_list_env *env)
{
	t_list_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_strcmp_export(var, tmp->str) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static void	ft_delete(t_list_env **env, t_list_env *searched)
{
	t_list_env	*tmp;

	tmp = *env;
	if (!env || !*env || !searched)
		return ;
	while (tmp != NULL && tmp != searched)
		tmp = (tmp)->next;
	if ((tmp)->prev == NULL)
	{
		*env = (tmp)->next;
		if (*env != NULL)
			(*env)->prev = NULL;
	}
	else if ((tmp)->next == NULL)
		((tmp)->prev)->next = NULL;
	else
	{
		((tmp)->prev)->next = (tmp)->next;
		((tmp)->next)->prev = (tmp)->prev;
	}
	free(tmp);
	tmp = NULL;
}

int	ft_unset(char **arg, t_list_env **env)
{
	int			i;
	int			count;
	t_list_env	*var;

	i = 1;
	var = NULL;
	count = count_arg(arg);
	if (count < 2)
		return (1);
	while (i < count)
	{
		var = ft_exist(arg[i], *env);
		if (var != NULL && ft_isequal(arg[i]) == 0)
			ft_delete(env, var);
		i++;
	}
	return (1);
}
