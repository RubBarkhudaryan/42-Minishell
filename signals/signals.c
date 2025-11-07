/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/09/23 17:47:54 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/23 17:47:54 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./signals.h"

void	sigint_handler_parent(int signo)
{
	(void)signo;
	write(STDOUT_FILENO, "\n", 1);

	if (g_status == 0)
	{
		if (rl_line_buffer)
			rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_status = 0;
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_heredoc_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
}
