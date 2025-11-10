/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 22:28:03 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/10 19:48:18 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./execute.h"

int	get_exit_code(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}

int	has_heredoc(t_cmd *cmd)
{
	t_redir	*redirs;

	if (!cmd->redirs_cmd)
		return (0);
	redirs = cmd->redirs_cmd->redirs;
	while (redirs)
	{
		if (redirs->type == TK_HEREDOC)
			return (1);
		redirs = redirs->next;
	}
	return (0);
}
