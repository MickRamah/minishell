/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:05:00 by zramahaz          #+#    #+#             */
/*   Updated: 2024/09/21 14:22:22 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    append_in_str(char **str, char *str_env)
{
    int i;
    char    *tmp;
    
    i = 0;
    while (str_env[i] != '=' && str_env[i])
        i++;
    i++;
    tmp = ft_strjoin(*str, &str_env[i]);
    free(*str);
    if (tmp == NULL)
        exit (1);
    *str = tmp;
}

int len_var(char *line, char *str)
{
    int len_line;
    int len_str;

    len_line = 0;
    len_str = 0;
    while (line[len_line] && line[len_line] != ' ' && ft_isalnum(line[len_line]))
        len_line++;
    while (str[len_str] && str[len_str] != '=')
        len_str++;
    if (len_line > len_str)
        len_str = len_line;
    return (len_str);
}

int    exist_in_env(char *line, t_list_env *env, int *index, char **str)
{
    int i;

    i = 0;
    while (env)
    {
        if (strncmp(&line[*index + 1], env->str, len_var(&line[*index + 1], env->str)) == 0)
        {
            append_in_str(str, env->str);
            *index += ft_strlen(env->str) - \
				ft_strlen(ft_strchr(env->str, '=')) + 1;
            return (1);
        }
        env = env->next;
    }
    return (0);
}
