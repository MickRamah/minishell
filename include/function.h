/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:51:43 by herakoto          #+#    #+#             */
/*   Updated: 2024/12/04 17:10:55 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "types.h"
# include <signal.h>

int		count_arg(char **arg);

// signal handling
void	ft_end_of_file(t_data *data);
void	ft_signal_handler(void);

//utils
int		ft_strlen_export(char *str);
void	*ft_free_var(t_data *data);
void	*ft_free_var_exec(t_data *data, pid_t **pid);
#endif
