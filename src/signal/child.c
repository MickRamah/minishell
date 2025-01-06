/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 15:05:38 by herakoto          #+#    #+#             */
/*   Updated: 2024/12/23 17:14:29 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_signal_check(int status)
{
	if (WTERMSIG(status) == 3)
		printf("Quit (core dumped)\n");
	else if (WTERMSIG(status) == 2)
		printf("\n");
	return (1);
}

void	ft_reset(void)
{
	struct sigaction	s_sa;
	t_signal			action;

	s_sa.sa_sigaction = handle_sigint;
	s_sa.sa_flags = SA_SIGINFO;
	sigemptyset(&(s_sa.sa_mask));
	action.state = GENERAL;
	set_signal_state(&action, 0);
	sigaction(SIGINT, &s_sa, NULL);
}
