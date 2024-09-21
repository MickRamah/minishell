/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:54:27 by zramahaz          #+#    #+#             */
/*   Updated: 2024/09/21 14:20:28 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list_env *ft_last_list(t_list_env *list)
{
    t_list_env  *last;

    last = list;
    while (last->next)
        last = last->next;
    return (last);
}

void    append(t_list_env **list, char *line)
{
    t_list_env *new;
    t_list_env *last;

    new = (t_list_env *)malloc(sizeof(t_list_env));
    if (new == NULL)
        exit(0);
    new->next = NULL;
    new->str = line;
    if (*list == NULL)
    {
        *list = new;
        (*list)->prev = NULL;
    }
    else
    {
        last = ft_last_list(*list);
        last->next = new;
        new->prev = last;
    }
}