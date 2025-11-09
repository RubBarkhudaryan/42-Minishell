/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:59:39 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/09 14:03:05 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

static bool	setup_cmd_from_redirs(t_cmd *cmd)
{
	if (cmd->redirs_cmd->argv)
	{
		cmd->cmd_name = ft_strdup(cmd->redirs_cmd->argv[0]);
		cmd->args = ft_splitdup(cmd->redirs_cmd->argv);
	}
	else
	{
		cmd->args = NULL;
		cmd->cmd_name = NULL;
	}
	return (cmd->cmd_name != NULL || cmd->args == NULL);
}

static bool	process_heredocs(t_cmd *cmd, t_shell *shell)
{
	t_redir	*tmp_red;
	char	*tmp;

	tmp_red = cmd->redirs_cmd->redirs;
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

static t_cmd	*handle_heredoc_redir(t_cmd *cmd, t_shell *shell)
{
	if (!setup_cmd_from_redirs(cmd))
		return (NULL);
	if (!process_heredocs(cmd, shell))
		return (free_cmd(cmd, 1), NULL);
	cmd->in_pipeline = -1;
	cmd->out_pipeline = -1;
	return (cmd);
}

static t_cmd	*handle_other_redirs(t_cmd *cmd)
{
	if (cmd->redirs_cmd->argv && cmd->redirs_cmd->argv[0])
		cmd->cmd_name = ft_strdup(cmd->redirs_cmd->argv[0]);
	else
		cmd->cmd_name = NULL;
	if (cmd->redirs_cmd->argv)
		cmd->args = ft_splitdup(cmd->redirs_cmd->argv);
	else
		cmd->args = NULL;
	cmd->in_pipeline = -1;
	cmd->out_pipeline = -1;
	return (cmd);
}

t_cmd	*parse_redirs_ast(t_cmd *cmd, t_token **token_list, t_shell *shell)
{
	cmd->redirs_cmd = parse_redirs(token_list);
	if (!cmd->redirs_cmd)
		return (free_redir_cmd(cmd->redirs_cmd, 0), free(cmd), NULL);
	if (cmd->redirs_cmd->redirs && cmd->redirs_cmd->redirs->type == TK_HEREDOC)
		return (handle_heredoc_redir(cmd, shell));
	else
		return (handle_other_redirs(cmd));
}
