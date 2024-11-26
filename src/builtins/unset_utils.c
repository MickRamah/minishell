/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:08:39 by herakoto          #+#    #+#             */
/*   Updated: 2024/11/19 12:11:05 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_count_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i] != NULL)
	{
		i++;
	}
	return (i);
}
