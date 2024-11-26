/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:37:12 by herakoto          #+#    #+#             */
/*   Updated: 2024/11/26 14:53:18 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>

static void	ft_update_oldpwd(t_data *data)
{
	t_list_env	*tmp;
	char		*oldpwd;

	tmp = data->env;
	while (tmp != NULL)
	{
		if (ft_strncmp("PWD", tmp->str, 3) == 0)
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		export("OLDPWD", &data->env);
	oldpwd = ft_strjoin("OLD", tmp->str);
	if (!oldpwd)
	{
		write(2, "malloc error\n", 13);
		return ;
	}
	export(oldpwd, &data->env);
	free(oldpwd);
}

static void	ft_update_pwd(t_data *data, char *arg)
{
	char	cwd[PATH_MAX];
	char	*pwd;
	t_list_env	*tmp;


	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		perror(arg);
		return ;
	}
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
	{
		write(2, "malloc error\n", 13);
		return ;
	}
	export(pwd, &data->env);
	printf("pwd: %s\n", pwd);
	free(pwd);
}

int	ft_cd(t_data *data, char **arg)
{
	int	fd;

	if (ft_count_arg(arg) == 2)
	{
		fd = chdir(arg[1]);
		if (fd == 0)
		{
			ft_update_oldpwd(data);
			ft_update_pwd(data, arg[1]);
		}
		else if (fd == -1)
			perror(arg[1]);
		return (fd);
	}
	write(2, "too many arguments\n", 20);
	return (1);
}
