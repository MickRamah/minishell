/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:00:16 by zramahaz          #+#    #+#             */
/*   Updated: 2024/11/09 14:01:38 by zramahaz         ###   ########.fr       */
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
# include <signal.h>
# include <limits.h>

# define INPUT		1	//"<"
# define HEREDOC	2	//"<<"
# define TRUNC		3	//">"
# define APPEND		4	//">>"
# define PIPE		5	//"|"
# define CMD		6	//"|"
# define ARG		7	//"|"
# define TMP_FILE	"heredoc.tmp"
// # define ARG_MAX	256

typedef struct s_list_env
{
	char				*str;
	struct s_list_env	*next;
	struct s_list_env	*prev;
}	t_list_env;

typedef struct s_token
{
	char			*str;
	bool			quote;
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
	bool		dq;
	int			exit_code;
	t_token		*token;
	t_list_env	*env;
	t_cmd		*cmd;
}	t_data;

/* parsing */
int			check_quote(t_data *data, char *line);
void		change_quote(char c, bool *dq, bool *sq);

int			replace_dollar(char **line, t_data *data);
int			exist_in_env(char *line, t_list_env *env, int *index, char **str);
int			len_var(char *line, char *str);

int			create_list_token(t_token **begin, char *command);
int			append_in_token(t_token **begin, char *line, int type);
int			add_special(t_token **begin, char **command);
int			is_special(char *command);

int			create_list_cmd(t_data *data);
int			ft_check_error(t_token *begin, t_data *data);
int			add_to_cmd(t_cmd *new, t_token **begin, t_data *data);
int			get_out(t_cmd *command, t_token *token);
int			get_in(t_cmd *command, t_token *token, t_data *data);

/* utils */
void		print_env(t_list_env *env);
void		print_token(t_token *token);
void		print_cmd(t_cmd *cmd);

void		free_env(t_list_env **env);
void		free_token(t_token **list);
void		free_cmd(t_cmd **cmd);
void		free_array(char **tab);
void		free_data(t_data *data, int ext);

t_list_env	*ft_last_list_env(t_list_env *list);
t_token		*ft_last_list_token(t_token *list);
t_cmd		*ft_last_list_cmd(t_cmd *command);
int			append_in_env(t_list_env **list, char *line);

bool		is_space(char c);
size_t		ft_strspn(const char *s, const char *accept);
int			check_pipe(t_data *data, t_token *token);

/* exec */
void		exec(t_data *data);
void		ft_for_child(t_data *data, t_cmd *command, int *pipe_fd);
void		redirection(t_cmd *command, int *pipe_fd);
char		**get_current_env(t_list_env *env, int i, int lenght_list);

int			here_doc(char *word, t_data *data, bool quote);
int			check_file(t_data *data, char *cmd_line, char **path \
				, struct stat buffer);

int			is_buildin(t_cmd *command);
void		build(t_data *data, t_cmd *command, int *pipe_fd);

/* builtins */
int			ft_pwd(void);
int			ft_env(t_list_env *env);
int			ft_is_void(char *str);
int			ft_export(char **str, t_list_env **env);
bool		export(char *str, t_list_env **env);
int			ft_strlen_export(char *str);
int			ft_unset(char **arg, t_list_env **env);
void		ft_exit(t_data *data, char **args);
int			ft_echo(char **args);
int			ft_cd(t_data *data, char **arg);
int			count_arg(char **arg);
int			ft_strlen_export(char *str);

#endif
