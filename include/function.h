/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 13:51:43 by herakoto          #+#    #+#             */
/*   Updated: 2024/12/03 18:37:54 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTION_H
# define FUNCTION_H

# include "types.h"

int	count_arg(char **arg);

// signal handling
void	ft_end_of_file(t_data *data);
void	ft_signal_handler();

//utils
int		ft_free_var(t_data *data);

#endif

