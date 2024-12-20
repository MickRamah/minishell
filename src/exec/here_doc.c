/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:32:32 by zramahaz          #+#    #+#             */
/*   Updated: 2024/11/09 14:06:08 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static bool	read_in_stdin(int fd, char *word, t_data *data, bool quote)
{
	char	*buf;

	while (1)
	{
		buf = readline("> ");
		if (!buf)
			break ;
		if (!ft_strncmp(word, buf, INT_MAX))
			break ;
		if (quote)
		{
			write(fd, buf, ft_strlen(buf));
			write(fd, "\n", 1);
			free(buf);
			continue ;
		}
		if (!replace_dollar(&buf, data))
			free_data(data, 1);
		write(fd, buf, ft_strlen(buf));
		write(fd, "\n", 1);
		free(buf);
	}
	free(buf);
	close(fd);
	return (true);
}

int	here_doc(char *word, t_data *data, bool quote)
{
	int	fd;

	fd = open(TMP_FILE, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	if (!read_in_stdin(fd, word, data, quote))
	{
		unlink(TMP_FILE);
		return (-1);
	}
	fd = open(TMP_FILE, O_RDONLY);
	if (fd > 0)
		unlink(TMP_FILE);
	return (fd);
}
