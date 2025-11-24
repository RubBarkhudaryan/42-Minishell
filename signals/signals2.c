/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 03:29:47 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/13 03:29:47 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./signals.h"

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	check_exit_status(t_shell *shell)
{
	if (g_status != 0)
	{
		shell->last_exit_code = 128 + g_status;
		g_status = 0;
	}
}
