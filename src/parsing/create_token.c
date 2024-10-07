/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:02:56 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/07 08:03:16 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    append_in_token(t_token **begin, char *line, int type)
{
    t_token *new;
    t_token *last;

    new = (t_token *)malloc(sizeof(t_token));
    if (!new)
        exit (1);
    new->next = NULL;
    new->type = type;
    new->str = ft_strdup(line);
    if (!new->str)
        exit (1);
    if (*begin == NULL)
    {
        *begin = new;
        new->prev = NULL;
        return ;
    }
    last = ft_last_list_token(*begin);
    last->next = new;
    new->prev = last;
}

void    change_str(char *command, char *tmp, int size)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (command[i + j] && i < size)
    {
        if (command[i + j] == '"')
        {
            j++;
            while (command[i + j] != '"')
            {
                   i++;
                   tmp[i - 1] = command[i + j - 1];
            }
            j++;
        }
        else if (command[i + j] == '\'')
        {
            j++;
            while (command[i + j] != '\'')
            {
                   i++;
                   tmp[i - 1] = command[i + j - 1];
            }
            j++;
        }
        else
        {
            tmp[i] = command[i + j];
            i++;
        }
    }
    tmp[i] = 0;
}

void len_cmd(char *command, int *quote, int *lenght)
{
    while (command[*lenght] && command[*lenght] != ' ')
    {
        if (command[*lenght] == '"')
        {
            (*quote)++;
            ++(*lenght);
            while (command[*lenght] && command[*lenght] != '"')
                (*lenght)++;
            (*quote)++;
            if (command[*lenght])
                (*lenght)++;
        }
        else if (command[*lenght] == '\'')
        {
            (*quote)++;
            ++(*lenght);
            while (command[*lenght] && command[*lenght] != '\'')
                (*lenght)++;
            (*quote)++;
            if (command[*lenght])
                (*lenght)++;
        }
        if (command[*lenght] && command[*lenght] != ' ' \
            && command[*lenght] != '"' && command[*lenght] != '\'')
            (*lenght)++;
    }
}

void    add_cmd(t_token **begin, char **command)
{
    int lenght;
    int quote;
    char    *tmp;
    t_token *last;

    quote = 0;
    lenght = 0;
    len_cmd(*command, &quote, &lenght);
    tmp = (char *)malloc(sizeof(char) * (lenght - quote + 1));
    if (!tmp)
        exit (1);
    change_str(*command, tmp, lenght - quote);
    append_in_token(begin, tmp, 0);
    last = ft_last_list_token(*begin);
    if (last->prev == NULL || last->prev->type == PIPE)
        last->type = CMD;
    else
        (last)->type = ARG;
    (*command) += lenght;
}

int create_list_token(t_token **begin, char *line)
{
    while (*line)
    {
        line += strspn(line, " ");
        if (is_special(line))
            add_special(begin, &line);
        else
            add_cmd(begin, &line);
    }
    return (1);
}
