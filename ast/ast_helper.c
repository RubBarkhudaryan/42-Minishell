/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:58:49 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/10 19:47:20 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

void	free_cmd(t_cmd *cmd, int flag_unlink_heredoc)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->cmd_name)
		free(cmd->cmd_name);
	if (cmd->args)
	{
		i = -1;
		while (cmd->args[++i])
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
		}
		free(cmd->args);
		cmd->args = NULL;
	}
	if (cmd->redirs_cmd)
		free_redir_cmd(cmd->redirs_cmd, flag_unlink_heredoc);
	free(cmd);
}

static t_cmd	*handle_redirection_cmd(t_cmd *cmd,
				bool is_expand, t_token **token_list)
{
	cmd->token_list = *token_list;
	while ((*token_list) && ((*token_list)->token_type == TK_WORD
			|| is_redir(*token_list)))
		(*token_list) = (*token_list)->next;
	cmd->args = NULL;
	cmd->cmd_name = NULL;
	cmd->in_subshell = false;
	cmd->is_expand = is_expand;
	cmd->in_pipeline = -1;
	cmd->out_pipeline = -1;
	cmd->redirs_cmd = NULL;
	return (cmd);
}

static t_cmd	*handle_regular_cmd(t_cmd *cmd,
				bool is_expand, t_token **token_list)
{
	int	arg_count;

	cmd->redirs_cmd = NULL;
	cmd->token_list = NULL;
	arg_count = count_args(*token_list);
	if ((*token_list)->token)
		cmd->cmd_name = ft_strdup((*token_list)->token);
	else
		cmd->cmd_name = NULL;
	cmd->in_pipeline = -1;
	cmd->out_pipeline = -1;
	cmd->in_subshell = false;
	cmd->is_expand = is_expand;
	if (!fill_args(cmd, token_list, arg_count))
		return (free_cmd(cmd, 0), NULL);
	return (cmd);
}

t_cmd	*give_token_for_cmd(t_token **token_list,
		bool is_expand, t_shell *shell)
{
	t_cmd	*cmd;

	(void)shell;
	if (!token_list || !*token_list)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (is_redirection_type((*token_list)))
		return (handle_redirection_cmd(cmd, is_expand, token_list));
	else
		return (handle_regular_cmd(cmd, is_expand, token_list));
}
