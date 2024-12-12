/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:53:29 by zramahaz          #+#    #+#             */
/*   Updated: 2024/11/20 16:06:07 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// static int	*len_list_cmd(t_data *data, t_cmd *command)
// {
// 	int		len;
// 	int		*pid;

// 	len = 0;
// 	while (command)
// 	{
// 		len++;
// 		command = command->next;
// 	}
// 	printf("len = %d\n", len);
// 	pid = (pid_t *)malloc(sizeof(pid_t) * len);
// 	if (pid == NULL)
// 		free_data(data, 1);
// 	return (pid);
// }

static void	ft_for_parent(t_cmd *command, int *pipe_fd)
{
	close(pipe_fd[1]);
	if (command->infile >= 0)
		close(command->infile);
	if (command->next != NULL && command->next->infile == -2)
		command->next->infile = pipe_fd[0];
	else
		close(pipe_fd[0]);
}

static void	execute_command(t_data *data, t_cmd *command, int *pipe_fd, \
						int *child_process)
{
	*child_process = fork();
	if (*child_process < 0)
		free_data(data, 1);
	else if (*child_process == 0)
	{
		if (command == NULL || command->argv[0] == NULL \
			|| command->argv[0][0] == 0)
		{
			if (pipe_fd[0] && pipe_fd[0] != -1)
				close(pipe_fd[0]);
			if (pipe_fd[1] && pipe_fd[1] != -1)
				close(pipe_fd[1]);
			if (command && command->argv[0] && command->argv[0][0] == 0)
				write(2, "minishell: : command not found\n", 31);
			free_data(data, 127);
		}
		ft_for_child(data, command, pipe_fd);
	}
	else
		ft_for_parent(command, pipe_fd);
}

static void	wait_process_child(t_data *data, t_cmd *command, pid_t *pid)
{
	int	status;
	int	i;

	i = 0;
	while (command)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			data->exit_code = WEXITSTATUS(status);
		i++;
		command = command->next;
	}
}

void	exec(t_data *data)
{
	t_cmd		*command;
	int			pipe_fd[2];
	pid_t		pid[1024];
	int			i;

	command = data->cmd;
	if (command && command->argv[0] && command->next == NULL && \
		is_buildin(command))
	{
		build(data, command, NULL);
		return ;
	}
	i = 0;
	while (command != NULL)
	{
		if (pipe(pipe_fd) == -1)
			free_data(data, 1);
		pid[i] = 0;
		execute_command(data, command, pipe_fd, &pid[i]);
		command = command->next;
		i++;
	}
	wait_process_child(data, data->cmd, pid);
}
