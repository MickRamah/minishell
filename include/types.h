/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 10:46:14 by herakoto          #+#    #+#             */
/*   Updated: 2024/12/04 17:00:49 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>

typedef struct s_list_env
{
	char				*str;
	struct s_list_env	*next;
	struct s_list_env	*prev;
}				t_list_env;

typedef struct s_token
{
	char			*str;
	bool			quote;
	int				type;
	struct s_token	*next;
	struct s_token	*prev;
}				t_token;

typedef struct s_cmd
{
	char			**argv;
	int				outfile;
	int				infile;
	struct s_cmd	*next;
	struct s_cmd	*prev;
}				t_cmd;

typedef struct s_data
{
	bool		sq;
	bool		dq;
	int			exit_code;
	t_token		*token;
	t_list_env	*env;
	t_cmd		*cmd;
}				t_data;

#endif
