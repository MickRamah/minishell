/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:34:23 by zramahaz          #+#    #+#             */
/*   Updated: 2024/09/20 11:53:10 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    print_env(t_list_env *env)
{
    t_list_env  *begin;
    t_list_env  *last;

    begin = env;
    last = ft_last_list(env);
    while (begin)
    {
        printf("|%s|\n", begin->str);
        begin = begin->next;
    }
    printf("\n");
    // while (last)
    // {
    //     printf("%s\n", last->str);
    //     last = last->prev;
    // }
}