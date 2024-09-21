/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:27:33 by zramahaz          #+#    #+#             */
/*   Updated: 2024/09/21 16:53:25 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void    quoting_choice(bool *dq, bool *sq, int *index, char c)
// {
//     if ((c == '"' || c == '\'') && !*sq && !*dq)
//     {
//         if (c == '\'')
//             *sq = true;
//         else if (c == '"')
//             *dq = true;
//         if (index)
//             (*index)++;
//     }
//     else if ((c == '"' || c == '\'') && (*sq || *dq))
//     {
//         if (c == '\'')
//             *sq = false;
//         else if (c == '"')
//             *dq = false;
//         if (index)
//             (*index)++;
//     }
// }

// int check_quote(t_data *data, char *line)
// {
//     bool    sq;
//     bool    dq;
//     int i;

//     i = 0;
//     sq = false;
//     dq = false;
//     while (line[i])
//     {
//         quoting_choice(&dq, &sq, &i, line[i]);
//         if (line[i] && line[i] != '\'' && line[i] != '"')
//             i++;
//     }
//     if (sq || dq)
//     {
// 		data->exit_code = 2;
//         printf("open quote\n");
//         return (1);
//     }
//     return (0);
// }

int close_quote(char *line, int *i_ptr, char c)
{
    int i;

    i = *i_ptr;
    if (c == '\'')
    {
        while (line[i++])
        {
            if (line[i] == '\'')
            {
                *i_ptr = i;
                return (1);
            }
        }
        return (0);    
    }
    while (line[i++])
    {
        if (line[i] == '"')
        {
            *i_ptr = i;
            return (1);
        }
    }
    return (0);
}

int check_quote(t_data *data, char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '\'' && !close_quote(line, &i, '\''))
        {
            data->exit_code = 2;
            return (0);
        }
        else if (line[i] == '"' && !close_quote(line, &i, '"'))
        {
            data->exit_code = 2;
            return (0);
        }
        i++;
    }
    return (1);
}