/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zramahaz <zramahaz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:53:29 by zramahaz          #+#    #+#             */
/*   Updated: 2024/10/15 14:03:02 by zramahaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	p_children(t_data *data, char **argv)
{
	printf("je suis fils mon pid est %d\n", getpid());
	execve("/bin/ls", argv, NULL);
	exit (42);
}

void	exec(t_data *data)
{
	char	*argv[] = {"ls", NULL};
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Erreur fork");
		exit (1);
	}
	if (pid == 0)
	{
		p_children(data, argv);
	}
	else
	{
		wait();
		printf("je suis pere mon pid est %d\n", getpid());
	}
}
