/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:37:12 by herakoto          #+#    #+#             */
/*   Updated: 2024/11/21 17:35:10 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(t_data *data, char *path);

static int	cd_no_arg(t_data *data)
{
	t_list_env	*tmp;
	char		*path;
	int			i;

	tmp = data->env;
	path = NULL;
	i = 0;
	while (tmp && ft_strncmp("HOME", tmp->str, 4) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return (0);
	path = tmp->str;
	while (path[i] && path[i] != '=')
		i++;
	if (path == NULL)
		return (0);
	return (cd(data, (path + (i + 1))));
}

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
	char	cwd[4096];
	char	*pwd;

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

int	cd(t_data *data, char *path)
{
	int	fd;

	fd = chdir(path);
	if (fd == 0)
	{
		ft_update_oldpwd(data);
		ft_update_pwd(data, path);
	}
	else if (fd == -1)
		perror(path);
	return (fd);
}

int	ft_cd(t_data *data, char **arg)
{
	if (count_arg(arg) == 1)
		return (cd_no_arg(data));
	if (count_arg(arg) == 2)
		return (cd(data, arg[1]));
	else if (count_arg(arg) > 2)
		write(2, "too many arguments\n", 20);
	return (1);
}
