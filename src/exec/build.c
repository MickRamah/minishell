/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:16:09 by zramahaz          #+#    #+#             */
/*   Updated: 2024/11/20 17:24:19 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_buildin(t_cmd *command)
{
	char	*str;

	str = command->argv[0];
	if (ft_strncmp("pwd", str, INT_MAX) == 0)
		return (1);
	else if (ft_strncmp("exit", str, INT_MAX) == 0)
		return (1);
	else if (ft_strncmp("echo", str, INT_MAX) == 0)
		return (1);
	else if (ft_strncmp("env", str, INT_MAX) == 0)
		return (1);
	else if (ft_strncmp("export", str, INT_MAX) == 0)
		return (1);
	else if (ft_strncmp("unset", str, INT_MAX) == 0)
		return (1);
	else if (ft_strncmp("cd", str, INT_MAX) == 0)
		return (1);
	return (0);
}

static void	build_execution_2(t_data *data, t_cmd *command)
{
	if (!ft_strncmp("env", command->argv[0], 3))
		*(data->exit_code) = ft_env(data->env);
	else if (!ft_strncmp("export", command->argv[0], 6))
		*(data->exit_code) = ft_export(command->argv, &data->env);
	else if (!ft_strncmp("unset", command->argv[0], 5))
		*(data->exit_code) = ft_unset(command->argv, &data->env);
}

static void	build_execution(t_data *data, t_cmd *command, int save_out)
{
	if (ft_strncmp("pwd", command->argv[0], 3) == 0)
		*(data->exit_code) = ft_pwd();
	else if (!ft_strncmp("echo", command->argv[0], 4))
		*(data->exit_code) = ft_echo(command->argv);
	else if (!ft_strncmp("cd", command->argv[0], 2))
		*(data->exit_code) = ft_cd(data, command->argv);
	else if (ft_strncmp("exit", command->argv[0], 4) == 0)
	{
		if (command->outfile >= 0)
		{
			dup2(save_out, STDOUT_FILENO);
			close(save_out);
		}
		ft_exit(data, command->argv);
	}
	build_execution_2(data, command);
}

static void	ft_dup(t_cmd *command, int *save_out)
{
	*save_out = dup(1);
	dup2(command->outfile, 1);
	close(command->outfile);
	if (*save_out >= 0 && command->next != NULL)
		close(*save_out);
}

void	build(t_data *data, t_cmd *command, int *pipe_fd)
{
	int		save_out;

	save_out = -1;
	if (pipe_fd != NULL)
	{
		if (command->outfile < 0 && command->next != NULL)
			command->outfile = pipe_fd[1];
		else
			close(pipe_fd[1]);
		// ft_close_all_fd(command);
	}
	if (command->outfile >= 0)
		ft_dup(command, &save_out);
	build_execution(data, command, save_out);
	if (command->outfile >= 0)
	{
		dup2(save_out, STDOUT_FILENO);
		close(save_out);
	}
}
