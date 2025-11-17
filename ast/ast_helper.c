/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:58:49 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/17 16:00:38 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->cmd_name = NULL;
	cmd->redirs_cmd = NULL;
	cmd->token_list = NULL;
	cmd->in_pipeline = -1;
	cmd->out_pipeline = -1;
	return (cmd);
}

void	free_cmd(t_cmd *cmd, int flag_unlink_heredoc)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->cmd_name)
		free(cmd->cmd_name);
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			cmd->args[i] = NULL;
			++i;
		}
		free(cmd->args);
		cmd->args = NULL;
	}
	if (cmd->redirs_cmd)
		free_redir_list(cmd->redirs_cmd, flag_unlink_heredoc);
	free(cmd);
}

t_cmd	*make_cmd(t_token **list, t_shell *shell)
{
	t_cmd	*cmd;
	int		type;
	int		i;
	t_redir	*last_redir;

	(void)shell;
	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	cmd->args = ft_calloc((count_args(*list) + 1), sizeof(char *));
	if (!cmd->args)
		return (free(cmd), NULL);
	i = 0;
	last_redir = NULL;
	while ((*list) && is_valid_token_type((*list)->type))
	{
		if ((*list)->type == TK_WORD)
		{
			cmd->args[i] = ft_strdup((*list)->token);
			if (!cmd->args[i])
				return (free_cmd(cmd, 1), NULL);
			i++;
		}
		else
		{
			type = (*list)->type;
			(*list) = (*list)->next;
			if (!(*list))
				return (free_cmd(cmd, 1), NULL);
			if (!cmd->redirs_cmd)
			{
				cmd->redirs_cmd = init_redir(type, (*list)->token);
				last_redir = cmd->redirs_cmd;
			}
			else
			{
				last_redir->next = init_redir(type, (*list)->token);
				last_redir = last_redir->next;
			}
			if (!last_redir)
				return (free_cmd(cmd, 1), NULL);
		}
		(*list) = (*list)->next;
	}
	cmd->args[i] = NULL;
	if (i > 0)
		cmd->cmd_name = ft_strdup(cmd->args[0]);
	return (cmd);
}
