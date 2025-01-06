/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:47:41 by herakoto          #+#    #+#             */
/*   Updated: 2024/11/11 18:13:41 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_list_env *env)
{
	t_list_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		if (ft_is_equal(tmp->str) == 1)
			printf("%s\n", tmp->str);
		tmp = tmp->next;
	}
	return (0);
}
