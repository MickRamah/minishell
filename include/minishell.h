/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:00:16 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/15 16:12:24 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdbool.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"

typedef struct s_list_env
{
	char				*str;
	struct s_list_env	*next;
	struct s_list_env	*prev;
}	t_list_env;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_cmd
{
	char			**argv;
	int				outfile;
	int				infile;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}	t_cmd;

typedef struct s_data
{
	bool		sq;
	int			exit_code;
	t_token		*token;
	t_list_env	*env;
	t_cmd		*cmd;
}	t_data;

int			check_quote(t_data *data, char *line);
int			replace_dollar(char **line, t_data *data);
int			create_list_token(t_token **begin, char *command);
int			create_list_cmd(t_data *data);
int			exist_in_env(char *line, t_list_env *env, int *index, char **str);
int			len_var(char *line, char *str);
bool		is_space(char c);
int			append_token(t_token **list, char *str, int type);
void		free_token(t_token **list);
void		print_token(t_token *token);
void		print_cmd(t_cmd *cmd);
void		append(t_list_env **list, char *line);
void		append_in_token(t_token **begin, char *line, int type);
int			free_list(t_list_env **list);
void		free_env(t_list_env **env);
void		free_cmd(t_cmd **cmd);
t_cmd		*ft_last_list_cmd(t_cmd *command);
t_token		*ft_last_list_token(t_token *list);
t_list_env	*ft_last_list_env(t_list_env *list);
int			is_special(char *command);
void		add_special(t_token **begin, char **command);
int			exec(t_data *data, char **env);
char	**ft_get_all_path(t_list_env *env);
char	*get_filename(t_token *token);

#endif
