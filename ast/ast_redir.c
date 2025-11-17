/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:59:39 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/17 15:14:53 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

bool	process_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_redir	*tmp_red;
	char	*tmp;

	tmp_red = cmd->redirs_cmd;
	while (tmp_red && tmp_red->type == TK_HEREDOC)
	{
		tmp = here_doc(cmd, ft_strdup(tmp_red->filename), shell);
		if (!tmp)
			return (false);
		free(tmp_red->filename);
		tmp_red->filename = tmp;
		tmp_red = tmp_red->next;
	}
	return (true);
}

// static t_cmd	*handle_heredoc_redir(t_cmd *cmd, t_shell *shell)
// {
// 	if (!process_heredocs(cmd, shell))
// 		return (free_cmd(cmd, 1), NULL);
// 	return (cmd);
// }

t_cmd	*parse_redirs_ast(t_cmd *cmd, t_token **token_list)
{
	int		type;
	t_redir	*last_redir;

	last_redir = NULL;
	while (*token_list && is_redir(*token_list))
	{
		type = (*token_list)->type;
		*token_list = (*token_list)->next;
		if (!(*token_list) || (*token_list)->type != TK_WORD)
			return (free_cmd(cmd, 0), NULL);
		if (!cmd->redirs_cmd)
		{
			cmd->redirs_cmd = init_redir(type, (*token_list)->token);
			last_redir = cmd->redirs_cmd;
		}
		else
		{
			last_redir->next = init_redir(type, (*token_list)->token);
			last_redir = last_redir->next;
		}
		if (!last_redir)
			return (free_cmd(cmd, 0), NULL);
		*token_list = (*token_list)->next;
	}
	return (cmd->in_pipeline = -1, cmd->out_pipeline = -1, cmd);
}
