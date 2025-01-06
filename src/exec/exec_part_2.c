/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_part_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 10:46:03 by zramahaz          #+#    #+#             */
/*   Updated: 2024/12/23 16:47:35 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	cmd_abs_or_courant_dir(char *cmd_line, char **path)
{
	*path = ft_strdup(cmd_line);
	if ((*path) == NULL)
		return ;
	if (access((*path), F_OK))
	{
		write(2, (*path), ft_strlen((*path)));
		write(2, " : command not found\n", 21);
		free(*path);
		*path = NULL;
	}
}

static char	**ft_get_all_path(t_list_env *env)
{
	char		*path;
	char		**all_path;

	path = NULL;
	all_path = NULL;
	while (env)
	{
		if (ft_strncmp(env->str, "PATH", len_var("PATH", env->str)) == 0)
		{
			path = &env->str[5];
			all_path = ft_split(path, ':');
			if (all_path == NULL)
				return (NULL);
			return (all_path);
		}
		env = env->next;
	}
	return (NULL);
}

static void	search_cmd(char *cmd_line, char **path, t_list_env *env)
{
	char		**all_path;
	char		*path_with_slash;
	int			i;

	if (!cherch_in_env("PATH", env))
		return (cmd_abs_or_courant_dir(cmd_line, path));
	all_path = ft_get_all_path(env);
	if (all_path == NULL)
		return ;
	i = 0;
	while (all_path && all_path[i])
	{
		path_with_slash = ft_strjoin(all_path[i++], "/");
		*path = ft_strjoin(path_with_slash, cmd_line);
		free(path_with_slash);
		if (access((*path), F_OK) == 0)
		{
			free_array(all_path);
			return ;
		}
		free(*path);
	}
	*path = NULL;
	free_array(all_path);
	ft_print_not_found(cmd_line);
}

static int	command_exist(t_data *data, char *cmd_line, char **path)
{
	struct stat	buffer;

	if (cmd_line[0] != '/' && cmd_line[0] != '.' && cmd_line[1] != '/')
		search_cmd(cmd_line, path, data->env);
	else
		cmd_abs_or_courant_dir(cmd_line, path);
	if ((*path) == NULL)
	{
		*(data->exit_code) = 127;
		return (0);
	}
	if (stat(*path, &buffer) == -1)
	{
		perror("stat failed");
		free(*path);
		*(data->exit_code) = 1;
		return (0);
	}
	if (check_file(data, cmd_line, path, buffer) == 0)
		return (0);
	return (1);
}

void	ft_for_child(t_data *data, t_cmd *command, int *pipe_fd)
{
	char	*path;
	char	**current_env;
	int		i;
	int		lenght_list;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = NULL;
	current_env = NULL;
	i = 0;
	lenght_list = 0;
	if (is_buildin(command))
		build(data, command, pipe_fd);
	else if (command_exist(data, command->argv[0], &path))
	{
		current_env = get_current_env(data->env, i, lenght_list);
		redirection(command, pipe_fd);
		execve(path, command->argv, current_env);
	}
	if (pipe_fd[0] && pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] && pipe_fd[1] != -1)
		close(pipe_fd[1]);
	if (command->outfile >= 0)
		close(command->outfile);
	free_data(data, *(data->exit_code));
}
