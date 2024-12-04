/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:07:16 by herakoto          #+#    #+#             */
/*   Updated: 2024/12/04 17:39:01 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <limits.h>

int	ft_pwd(void)
{
	char	current_directory[PATH_MAX];

	if (getcwd(current_directory, sizeof(current_directory)) != NULL)
		printf("%s\n", current_directory);
	else
	{
		perror("pwd: ");
		return (1);
	}
	return (0);
}
