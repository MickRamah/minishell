/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:44:06 by herakoto          #+#    #+#             */
/*   Updated: 2024/12/06 16:06:43 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_sigint_function(int sig, siginfo_t *siginfo, void *context)
{
	int	pid;

	(void)context;
	pid = siginfo->si_pid;
	write(1, "\n", 2);
	if (sig == SIGINT && pid > 0)
	{
		write(1, "parent\n", 8);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_signal_handler(void)
{
	struct sigaction	s_sa;

	s_sa.sa_sigaction = ft_sigint_function;
	s_sa.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sa.sa_mask);
	sigaction(SIGINT, &s_sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
