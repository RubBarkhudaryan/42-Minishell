/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:30:06 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/30 19:58:26 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer.h"

void	free_redir_list(t_redir *redir, int flag_unlink_heredoc)
{
	t_redir	*next;

	if (!redir)
		return ;
	while (redir)
	{
		next = redir->next;
		if (redir->type == TK_HEREDOC && flag_unlink_heredoc)
			unlink(redir->filename);
		free(redir->filename);
		free(redir);
		redir = next;
	}
}

void	free_redir_cmd(t_redir_cmd *cmd, int flag_unlink_heredoc)
{
	int			i;
	t_redir_cmd	*temp_cmd;
	t_redir_cmd	*temp_next_cmd;

	temp_cmd = cmd;
	while (temp_cmd)
	{
		free_redir_list(temp_cmd->redirs, flag_unlink_heredoc);
		if (temp_cmd->argv)
		{
			i = -1;
			while (temp_cmd->argv && temp_cmd->argv[++i])
				free(temp_cmd->argv[i]);
			free(temp_cmd->argv);
		}
		temp_next_cmd = temp_cmd->next;
		free(temp_cmd);
		temp_cmd = temp_next_cmd;
	}
}
