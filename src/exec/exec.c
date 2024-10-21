/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:53:29 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/15 14:03:02 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	execute_outfile(t_token *token)
{
	int	fd;

	while (token && token->str != NULL)
	{
		if (token->type == APPEND)
		{
			fd = open(token->next->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
			{
				perror("open output file failed");
				return;
            }
            dup2(fd, STDOUT_FILENO);
		    close(fd);
		}
		if (token->type == TRUNC)
		{
			fd = open(token->next->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
			{
				perror("open output file failed");
				return;
            }
            dup2(fd, STDOUT_FILENO);
		    close(fd);
		}
		token = token->next;
	}
}

void	execute_infile(t_token *token)
{
	int	fd;

	while (token && token->str != NULL)
	{
		if (token->type == INPUT)
		{
			fd = open(token->next->str, O_RDONLY);
            if (fd < 0)
			{
				perror("open output file failed");
				return;
            }
            dup2(fd, STDIN_FILENO);
		    close(fd);
		}
		token = token->next;
	}
}

void	command_exists(char *full_path, t_cmd *cmd, char **env, t_token *token)
{
	t_cmd	*command;
	pid_t	child_pid;

	command = cmd;
	child_pid = fork();
	if (child_pid < 0)
	{
		perror("Error fork");
		return ;
	}
	else if (child_pid == 0)
	{
		if (cmd->outfile == 1)
			execute_outfile(token);
		if (cmd->infile == 0)
			execute_infile(token);
		execve(full_path, command->argv, env);
	}
	wait(NULL);
}

void	loop_cmd(char **all_path, t_cmd *command, char **env, t_token *token)
{
	int		i;
	char	*path;
	char	*full_path;
	struct stat	buffer;

	i = 0;
	path = NULL;
	full_path = NULL;
	while (all_path[i])
	{
		path = ft_strjoin(all_path[i], "/");
		full_path = ft_strjoin(path, command->argv[0]);
		free(path);
		path = NULL;
		if (stat(full_path, &buffer) == 0)
		{
			command_exists(full_path, command, env, token);
			free(full_path);
			return ;
		}
		free(full_path);
		full_path = NULL;
		i++;
	}
	printf("command not found\n");
	return ;
}

int	exec(t_data *data, char **env)
{
	int		i;
	char	**all_path;
	t_cmd	*command;
	
	i = 0;
	all_path = ft_get_all_path(data->env);
	if (all_path == NULL)
		exit (0);
	command = data->cmd;
	while (command)
	{
		loop_cmd(all_path, command, env, data->token);
		command = command->next;
	}
	while (all_path[i])
	{
		free(all_path[i]);
		i++;
	}
	free(all_path);
	all_path = NULL;
}
