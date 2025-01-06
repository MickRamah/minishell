/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:53:29 by zramahaz          #+#    #+#             */
/*   Updated: 2024/12/23 17:13:22 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	*len_list_cmd(t_data *data, t_cmd *command)
{
	int		len;
	int		*pid;

	len = 0;
	while (command)
	{
		len++;
		command = command->next;
	}
	pid = (pid_t *)malloc(sizeof(pid_t) * len);
	if (pid == NULL)
		free_data(data, 1);
	return (pid);
}

static void	ft_for_parent(t_cmd *command, int *pipe_fd)
{
	close(pipe_fd[1]);
	if (command->infile >= 0)
		close(command->infile);
	if (command->next != NULL && command->next->infile == -2)
		command->next->infile = pipe_fd[0];
	else
		close(pipe_fd[0]);
	if (command->outfile >= 0)
		close(command->outfile);
}

static void	execute_command(t_data *data, t_cmd *command, \
							int *child_process, int pos)
{
	int			pipe_fd[2];

	if (pipe(pipe_fd) == -1)
		free_data(data, 1);
	*(child_process + pos) = fork();
	if (*(child_process + pos) < 0)
		free_data(data, 1);
	else if (*(child_process + pos) == 0)
	{
		if (!command || !(command->argv[0]) || !(command->argv[0][0]))
		{
			free(child_process);
			if (pipe_fd[0] && pipe_fd[0] != -1)
				close(pipe_fd[0]);
			if (pipe_fd[1] && pipe_fd[1] != -1)
				close(pipe_fd[1]);
			if (command && command->argv[0] == NULL)
				free_data(data, g_signal_code);
			write(2, "minishell: : command not found\n", 31);
			free_data(data, 127);
		}
		free(child_process);
		ft_for_child(data, command, pipe_fd);
	}
	ft_for_parent(command, pipe_fd);
}

static void	wait_process_child(t_data *data, t_cmd *command, pid_t *pid)
{
	int			status;
	int			i;
	static int	signal_state = 0;

	i = 0;
	status = 0;
	(void)data;
	while (command)
	{
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
			*(data->exit_code) = WEXITSTATUS(status);
		if (WIFSIGNALED(status) && signal_state == 0)
			signal_state = ft_signal_check(status);
		i++;
		command = command->next;
	}
	if (WIFSIGNALED(status))
		g_signal_code = 128 + WTERMSIG(status);
	signal_state = 0;
}

void	exec(t_data *data)
{
	t_cmd				*command;
	pid_t				*pid;
	int					i;

	signal(SIGINT, SIG_IGN);
	command = data->cmd;
	if (command && command->argv[0] && command->next == NULL && \
		is_buildin(command))
	{
		build(data, command, NULL);
		ft_reset();
		return ;
	}
	pid = len_list_cmd(data, command);
	i = 0;
	while (command != NULL)
	{
		pid[i] = 0;
		execute_command(data, command, pid, i);
		command = command->next;
		i++;
	}
	wait_process_child(data, data->cmd, pid);
	free(pid);
	ft_reset();
}
