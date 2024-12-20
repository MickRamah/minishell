/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:01:28 by zramahaz          #+#    #+#             */
/*   Updated: 2024/11/20 11:15:59 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/minishell.h"

int	g_signal_code;

void	create_env(t_data *data, int argc, char **argv, char **env)
{
	t_list_env	*list;
	int			i;
	char		*tmp;

	(void)argc;
	(void)argv;
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
	signal(SIGINT, handle_sigint);
	data->sq = false;
	data->dq = false;
	data->cmd = NULL;
	data->token = NULL;
	data->env = NULL;
	g_signal_code = 0;
	data->exit_code = &g_signal_code;
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

	status = 0;
	if (!check_quote(data, line))
	{
		free(line);
		return (0);
	}
	if (!replace_dollar(&line, data, status) \
		|| !create_list_token(data, &data->token, line, &status))
	{
		free(line);
		if (status == -1)
			return (0);
		write(2, "malloc ERROR\n", 13);
		free_data(data, 1);
	}
	free(line);
	if (!create_list_cmd(data))
	{
		free_token(&data->token);
		free_cmd(&data->cmd);
		return (0);
	}
	print_token(data->token);
	print_cmd(data->cmd);
	return (check_pipe(data, data->token));
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	char	*line;

	init_data(&data);
	create_env(&data, argc, argv, env);
	while (1)
	{
		line = readline("minishell> ");
		if (line == NULL)
		{
			printf("exit\n");
			free_data(&data, *(data.exit_code));
		}
		if (empty_line(line))
			continue ;
		add_history(line);
		if (!parseline(&data, line))
			continue ;
		exec(&data);
		free_token(&data.token);
		free_cmd(&data.cmd);
	}
	rl_clear_history();
	free_data(&data, -42);
	return (0);
}
