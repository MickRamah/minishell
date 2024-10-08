/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:18:35 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/07 14:55:49 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool	is_space(char c)
{
	if (c && (c == ' ' || c == '\n' || c == '\r' || c == '\f' || c == '\t' \
	|| c == '\v'))
		return (true);
	return (false);
}

int is_special(char *command)
{
    int len;

    len = ft_strlen(command);
    if (len >= 2)
    {
        if (ft_strncmp(command, ">>", 2) == 0)
            return (APPEND);
        if (ft_strncmp(command, "<<", 2) == 0)
            return (HEREDOC);
    }
    if (len >= 1)
    {
        if (ft_strncmp(command, "|", 1) == 0)
            return (PIPE);
        if (ft_strncmp(command, ">", 1) == 0)
            return (TRUNC);
        if (ft_strncmp(command, "<", 1) == 0)
            return (INPUT);
    }
    return (0);
}

void    add_special(t_token **begin, char **command)
{
    int val;

    val = is_special(*command);
    if (val == APPEND)
        append_in_token(begin, ft_strdup(">>"), APPEND);
    if (val == HEREDOC)
        append_in_token(begin, ft_strdup("<<"), HEREDOC);
    if (val == TRUNC)
        append_in_token(begin, ft_strdup(">"), TRUNC);
    if (val == INPUT)
        append_in_token(begin, ft_strdup("<"), INPUT);
    if (val == PIPE)
        append_in_token(begin, ft_strdup("|"), PIPE);
    if (val == APPEND || val == HEREDOC)
        (*command) += 2;
    else if (val == TRUNC || val == INPUT || val == PIPE)
        (*command)++;
}