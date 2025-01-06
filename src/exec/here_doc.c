/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:32:32 by zramahaz          #+#    #+#             */
/*   Updated: 2024/12/20 18:45:35 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_buf_and_signal(char *buf, char *word)
{
	int	tty;
	int	*status;

	status = get_addr_var_stat();
	if (buf == NULL)
	{
		if (g_signal_code == -10)
		{
			tty = open("/dev/tty", O_RDONLY);
			if (tty == -1)
				return (0);
			dup2(tty, 0);
		}
		else
		{
			write(2, "warning: here-document delimited by end-of-file ", 48);
			write(2, "(wanted '", 9);
			write(2, word, ft_strlen(word));
			write(2, "')\n", 3);
			*status = 1;
			g_signal_code = 0;
		}
		return (0);
	}
	return (1);
}

static void	read_in_stdin(int fd, char *word, t_data *data, bool quote)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (check_buf_and_signal(buf, word) == 0)
			break ;
		if (ft_strncmp(word, buf, INT_MAX) == 0)
			break ;
		if (quote)
		{
			write(fd, buf, ft_strlen(buf));
			write(fd, "\n", 1);
			free(buf);
			continue ;
		}
		if (!replace_dollar(&buf, data, 0))
			free_data(data, 1);
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	free(buf);
}

int	here_doc(char *word, t_data *data, bool quote)
{
	int			fd;
	t_signal	heredocs;

	heredocs.state = HEREDOCS;
	set_signal_state(&heredocs, 0);
	fd = open(TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	read_in_stdin(fd, word, data, quote);
	close(fd);
	heredocs.state = GENERAL;
	set_signal_state(&heredocs, 0);
	fd = open(TMP_FILE, O_RDONLY);
	if (fd > 0)
		unlink(TMP_FILE);
	return (fd);
}

int	check_file(t_data *data, char *cmd_line, char **path, struct stat buffer)
{
	if (!S_ISREG(buffer.st_mode))
	{
		write(2, cmd_line, ft_strlen(cmd_line));
		write(2, " : Is a directory\n", 18);
		free(*path);
		*(data->exit_code) = 126;
		return (0);
	}
	if (!(buffer.st_mode & S_IXUSR) && !(buffer.st_mode & S_IXGRP) \
			&& !(buffer.st_mode & S_IXOTH))
	{
		write(2, cmd_line, ft_strlen(cmd_line));
		write(2, " : Permission denied\n", 21);
		free(*path);
		*(data->exit_code) = 126;
		return (0);
	}
	return (1);
}
