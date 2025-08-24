/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:58:49 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/24 20:54:48 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

void	free_cmd(t_cmd *cmd)
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
			free(cmd->args[i]);
		free(cmd->args);
	}
	free(cmd);
}

static int	is_valid_token_type(t_token_type type)
{
	return (type == TK_WORD || type == TK_SINGLE_QUOTE
		|| type == TK_DOUBLE_QUOTE || type == TK_DOLLAR
		|| type == TK_REDIR_INPUT || type == TK_REDIR_OUTPUT
		|| type == TK_APPEND || type == TK_HEREDOC);
}

static int	count_args(t_token *current)
{
	int	count;

	count = 0;
	while (current && is_valid_token_type(current->token_type))
	{
		count++;
		current = current->next;
	}
	return (count);
}

static int	fill_args(t_cmd *cmd, t_token **token_list, int arg_count)
{
	int	i;

	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return (0);
	i = 0;
	while (*token_list && is_valid_token_type((*token_list)->token_type))
	{
		cmd->args[i] = ft_strdup((*token_list)->token);
		if (!cmd->args[i])
		{
			free_cmd(cmd);
			return (0);
		}
		*token_list = (*token_list)->next;
		i++;
	}
	cmd->args[i] = NULL;
	return (1);
}

t_cmd	*give_token_for_cmd(t_token **token_list)
{
	t_cmd	*cmd;
	int		arg_count;

	if (!token_list || !*token_list)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
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
