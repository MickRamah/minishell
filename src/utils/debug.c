/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:34:23 by zramahaz          #+#    #+#             */
/*   Updated: 2024/09/28 15:25:43 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    print_env(t_list_env *env)
{
    t_list_env  *begin;
    t_list_env  *last;

    begin = env;
    last = ft_last_list_env(env);
    while (begin)
    {
        printf("|%s|\n", begin->str);
        begin = begin->next;
    }
    printf("\n");
}

void    print_token(t_token *env)
{
    t_token  *begin;
    t_token  *last;

    begin = env;
    while (begin)
    {
        printf("|%s| [%d]\n", begin->str, begin->type);
        begin = begin->next;
    }
    printf("\n");
}