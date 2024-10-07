/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:00:16 by zramahaz          #+#    #+#             */
/*   Updated: 2024/09/28 17:11:22 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"

typedef struct s_list_env
{
    char    *str;
    struct s_list_env *next;
    struct s_list_env *prev;
}   t_list_env;

typedef struct s_token
{
    char    *str;
    int     type;
    struct s_token  *next;
    struct s_token  *prev;
}   t_token;

typedef struct s_data
{
    bool    sq;
    int exit_code;
    t_token *token;
    t_list_env  *env;
}   t_data;


/*               parsing            */
// quote.c
int check_quote(t_data *data, char *line);
// void    quoting_choice(bool *dq, bool *sq, int *index, char c);
//dollar_replace
int    replace_dollar(char **line, t_data *data);
// create_token.c
int    create_list_token(t_token **begin, char *command);
// dollar_env.c
int    exist_in_env(char *line, t_list_env *env, int *index, char **str);
int len_var(char *line, char *str);


/*               utils              */
// ms_utils.c
bool	is_space(char c);
// list_token.c
int	append_token(t_token **list, char *str, int type);
void	free_token(t_token **list);
// debug.c
void    print_token(t_token *token);
// list_utils.c
void	append(t_list_env **list, char *line);
int	free_list(t_list_env **list);
// ft_free.c
void    free_env(t_list_env **env);


t_token *ft_last_list_token(t_token *list);
t_list_env *ft_last_list_env(t_list_env *list);
int is_special(char *command);
void    add_special(t_token **begin, char **command);

#endif