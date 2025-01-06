/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:23:40 by zramahaz          #+#    #+#             */
/*   Updated: 2024/12/23 16:51:11 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_close_all_fd(t_cmd *command)
{
	while (command)
	{
		if (command->infile >= 0)
			close(command->infile);
		if (command->outfile >= 0)
			close(command->outfile);
		command = command->next;
	}
}

void	redirection(t_cmd *command, int *pipe_fd)
{
	close(pipe_fd[0]);
	if (command->infile >= 0)
	{
		dup2(command->infile, STDIN_FILENO);
		close(command->infile);
	}
	if (command->outfile >= 0)
	{
		dup2(command->outfile, STDOUT_FILENO);
		close(command->outfile);
	}
	else if (command->next != NULL)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	close(pipe_fd[1]);
	ft_close_all_fd(command);
}

char	**get_current_env(t_list_env *env, int i, int lenght_list)
{
	char		**dest;
	t_list_env	*list;

	list = env;
	while (list)
	{
		lenght_list++;
		list = list->next;
	}
	dest = (char **)malloc(sizeof(char *) * (lenght_list + 1));
	if (dest == NULL)
		return (NULL);
	while (i < lenght_list)
	{
		dest[i] = ft_strdup(env->str);
		if (dest[i] == NULL)
		{
			free_array(dest);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	dest[i] = NULL;
	return (dest);
}

int	cherch_in_env(char *path, t_list_env *env)
{
	while (env)
	{
		if (!ft_strncmp(path, env->str, len_var(path, env->str)))
			return (1);
		env = env->next;
	}
	return (0);
}

void	ft_print_not_found(char *cmd_line)
{
	write(2, cmd_line, ft_strlen(cmd_line));
	write(2, " : command not found\n", 21);
}
