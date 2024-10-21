/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:01:28 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/11 14:02:32 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

void	create_env(t_data *data, char **env)
{
	t_list_env	*list;
	int			i;
	char		*tmp;

	i = 0;
	list = NULL;
	while (env[i])
	{
		tmp = ft_strdup(env[i]);
		if (tmp == NULL)
			exit(0);
		append(&list, tmp);
		i++;
	}
	data->env = list;
}

void	init_data(t_data *data)
{
	data->sq = false;
	data->cmd = NULL;
	data->token = NULL;
	data->env = NULL;
	data->exit_code = 0;
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (i == (int)ft_strlen(line))
	{
		free(line);
		return (1);
	}
	return (0);
}

int	parseline(t_data *data, char *line)
{
	t_token	*last;
	int		i;

	if (!check_quote(data, line))
	{
		printf("quote is open\n");
		return (0);
	}
	if (!replace_dollar(&line, data))
	{
		free(line);
		printf("malloc ERROR\n");
		exit (0);
	}
	if (!create_list_token(&data->token, line))
	{
		free(line);
		printf("malloc ERROR\n");
		exit (0);
	}
	free(line);
	print_token(data->token);
	last = ft_last_list_token(data->token);
	if (last->type == PIPE)
	{
		write(2, "Error: Unclosed pipe\n", 21);
		data->exit_code = 2;
		return (0);
	}
	if (!create_list_cmd(data))
		return (0);
	print_cmd(data->cmd);
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*line;
	// int	i;

	// i = 1;
	init_data(&data);
	create_env(&data, env);
	while (42/*&& i > 0*/)
	{
		line = readline("minishell> ");
		if (line == NULL)
			return (1);
		if (empty_line(line))
			continue ;
		add_history(line);
		if (!parseline(&data, line))
		{
			free(line);
			free_token(&data.token);
			continue ;
		}
		exec(&data, env);
		free(line);
		free_token(&data.token);
		free_cmd(&data.cmd);
		// i--;
	}
	// i = 0;
	// while (i++ < history_length)
	// 	rl_clear_history();
	free_env(&data.env);
	return (0);
}
