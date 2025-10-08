/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:58:49 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/08 18:15:36 by apatvaka         ###   ########.fr       */
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

int	is_redirection_type(t_token *token)
{
	while (token)
	{
		if (token->token_type == TK_REDIR_INPUT
			|| token->token_type == TK_REDIR_OUTPUT
			|| token->token_type == TK_APPEND
			|| token->token_type == TK_HEREDOC)
			// || token->token_type == TK_R_PARENTHESIS)
			return (1);
		token = token->next;
	}
	return (0);
}

t_cmd	*give_token_for_cmd(t_token **token_list, t_shell *shell)
{
	t_cmd	*cmd;
	int		arg_count;

	if (!token_list || !*token_list)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (is_redirection_type((*token_list)))
		return (parse_redirs_ast(cmd, token_list, shell));
	cmd->redirs_cmd = NULL;
	arg_count = count_args(*token_list);
	cmd->cmd_name = ft_strdup((*token_list)->token);
	if (!cmd->cmd_name)
		return (free(cmd), NULL);
	cmd->in_pipeline = -1;
	cmd->out_pipeline = -1;
	if (!fill_args(cmd, token_list, arg_count))
		return (NULL);
	return (cmd);
}
