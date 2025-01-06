/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:00:16 by zramahaz          #+#    #+#             */
/*   Updated: 2024/12/23 16:52:38 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <stdbool.h>
# include <errno.h>
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

extern int	g_signal_code;

typedef enum e_state
{
	HEREDOCS,
	GENERAL
}			t_state;

typedef struct s_signal
{
	t_state	state;
}				t_signal;

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
	int			*exit_code;
	t_token		*token;
	t_list_env	*env;
	t_cmd		*cmd;
}	t_data;

/* builtins */
int			ft_cd(t_data *data, char **arg);

int			ft_echo(char **args);

int			ft_find_egal(char *str);
int			ft_env(t_list_env *env);

int			ft_export(char **str, t_list_env **env);
bool		export(char *str, t_list_env **env);

void		ft_exit(t_data *data, char **args);

int			ft_pwd(void);

int			ft_unset(char **arg, t_list_env **env);

int			ft_is_equal(char *str);
int			count_arg(char **arg);
int			ft_strlen_export(char *str);

/* exec */
int			is_buildin(t_cmd *command);
void		build(t_data *data, t_cmd *command, int *pipe_fd);

void		ft_for_child(t_data *data, t_cmd *command, int *pipe_fd);

void		ft_close_all_fd(t_cmd *command);
void		redirection(t_cmd *command, int *pipe_fd);
char		**get_current_env(t_list_env *env, int i, int lenght_list);
int			cherch_in_env(char *path, t_list_env *env);
void		ft_print_not_found(char *cmd_line);

void		exec(t_data *data);

int			here_doc(char *word, t_data *data, bool quote);
int			check_file(t_data *data, char *cmd_line, char **path \
				, struct stat buffer);

/* parsing */
int			get_out(t_cmd *command, t_token *token);
int			get_in(t_cmd *command, t_token *token, t_data *data);

int			ft_check_error(t_token *begin, t_data *data);
int			add_to_cmd(t_cmd *new, t_token **begin, t_data *data);

int			create_list_cmd(t_data *data);

int			append_in_token(t_token **begin, char *line, int type);
int			create_list_token(t_data *data, t_token **begin, char *command, \
								int *status);

int			len_var(char *line, char *str);
int			exist_in_env(char *line, t_list_env *env, int *index, char **str);

int			replace_dollar(char **line, t_data *data, int i);

void		change_quote(char c, bool *dq, bool *sq);
int			check_quote(t_data *data, char *line);

/* utils */
void		free_env(t_list_env **env);
void		free_token(t_token **list);
void		free_cmd(t_cmd **cmd);
void		free_data(t_data *data, int ext);
void		free_array(char **tab);

t_list_env	*ft_last_list_env(t_list_env *list);
t_token		*ft_last_list_token(t_token *list);
t_cmd		*ft_last_list_cmd(t_cmd *command);
int			append_in_env(t_list_env **list, char *line);

int			*get_addr_var_stat(void);

bool		is_space(char c);
int			is_special(char *command);
int			add_special(t_token **begin, char **command);
size_t		ft_strspn(const char *s, const char *accept);
int			check_pipe(t_data *data, t_token *token);

/* signals*/
int			ft_signal_check(int status);
void		ft_reset(void);
t_state		set_signal_state(t_signal *action, int n);
void		handle_sigint(int sig, siginfo_t *info, void *context);

#endif
