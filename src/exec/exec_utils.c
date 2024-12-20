/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:23:40 by zramahaz          #+#    #+#             */
/*   Updated: 2024/11/20 16:23:43 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
