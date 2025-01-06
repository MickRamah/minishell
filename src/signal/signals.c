/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herakoto <herakoto@student.42antanana      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:13:12 by herakoto          #+#    #+#             */
/*   Updated: 2024/12/23 16:01:16 by herakoto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_state	set_signal_state(t_signal *action, int n)
{
	static t_state	state;

	if (n == 0)
		state = action->state;
	return (state);
}

void	handle_sigint(int sig, siginfo_t *info, void *context)
{
	int				pid;
	int				*status;

	(void)sig;
	(void)context;
	pid = info->si_pid;
	status = get_addr_var_stat();
	if (*status == 0)
		write(STDOUT_FILENO, "\n", 2);
	if (set_signal_state(NULL, 1) == HEREDOCS)
	{
		close(0);
		g_signal_code = -10;
		*status = 1;
	}
	else if (set_signal_state(NULL, 1) == GENERAL)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		if (pid > 0)
			rl_redisplay();
		g_signal_code = 130;
	}
}
