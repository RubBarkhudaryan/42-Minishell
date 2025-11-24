/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 15:58:14 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/24 15:58:14 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

static int	add_arg(t_cmd **cmd, int index, char *value)
{
	(*cmd)->args[index] = ft_strdup(value);
	if (!(*cmd)->args[index])
		return (0);
	return (1);
}

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

t_cmd	*make_cmd(t_token **list)
{
	t_cmd	*cmd;
	int		i;

	cmd = init_cmd();
	if (!cmd || count_args(*list) == 0)
		return (NULL);
	cmd->args = ft_calloc((count_args(*list) + 1), sizeof(char *));
	if (!cmd->args)
		return (free(cmd), NULL);
	i = 0;
	while ((*list) && is_valid_token_type((*list)->type))
	{
		if ((*list)->type == TK_WORD)
		{
			if (!add_arg(&cmd, i, (*list)->token))
				return (free_cmd(cmd, 1), NULL);
			++i;
		}
		else if (!add_redir(&cmd->redirs_cmd, list))
			return (free_cmd(cmd, 1), NULL);
		(*list) = (*list)->next;
	}
	if (i > 0)
		cmd->cmd_name = ft_strdup(cmd->args[0]);
	return (cmd->args[i] = NULL, cmd);
}
