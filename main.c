/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:01:28 by zramahaz          #+#    #+#             */
/*   Updated: 2024/12/04 17:46:21 by herakoto         ###   ########.fr       */
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
		{
			free_env(&list);
			exit(1);
		}
		if (append_in_env(&list, tmp) == 0)
		{
			free_env(&list);
			write(2, "malloc error\n", 13);
			exit (1);
		}
		i++;
	}
	data->env = list;
}

void	init_data(t_data *data)
{
	data->sq = false;
	data->dq = false;
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
	int	status;

	if (!check_quote(data, line))
	{
		free(line);
		return (0);
	}
	if (!replace_dollar(&line, data) || !create_list_token(&data->token, line))
	{
		free(line);
		printf("malloc ERROR\n");
		free_data(data, 1);
	}
	free(line);
	print_token(data->token);
	if (!create_list_cmd(data))
	{
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (0);
	}
	print_cmd(data->cmd);
	status = check_pipe(data, data->token);
	return (status);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*line;

	(void)argc;
	(void)argv;
	ft_signal_handler();
	init_data(&data);
	create_env(&data, env);
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
			ft_end_of_file(&data);
		if (empty_line(line))
			continue ;
		add_history(line);
		if (!parseline(&data, line))
			continue ;
		exec(&data);
	}
	rl_clear_history();
	free_data(&data, -42);
	return (0);
}
