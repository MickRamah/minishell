/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 17:45:21 by herakoto          #+#    #+#             */
/*   Updated: 2024/12/04 16:56:33 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	*ft_free_var(t_data *data)
{
	if (data->token != NULL)
		free_token(&data->token);
	if (data->cmd != NULL)
		free_cmd(&data->cmd);
	return (NULL);
}

void	*ft_free_var_exec(t_data *data, pid_t **pid)
{
	ft_free_var(data);
	free(*pid);
	return (NULL);
}
