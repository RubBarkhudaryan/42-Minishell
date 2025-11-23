/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 13:55:44 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/23 20:36:55 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

int	is_subshell_paren(t_token *token)
{
	while (token)
	{
		if (token->type != TK_R_PARENTHESIS)
			return (1);
		token = token->next;
	}
	return (0);
}

char	**ft_splitdup(char **args)
{
	int		i;
	char	**ret;
	int		count;

	i = -1;
	count = args_len(args) + 1;
	ret = malloc(sizeof(char *) * count);
	if (!ret)
		return (NULL);
	while (args && args[++i])
	{
		ret[i] = ft_strdup(args[i]);
		if (!ret[i])
		{
			free_split(ret);
			return (NULL);
		}
	}
	ret[i] = NULL;
	return (ret);
}

int	is_valid_token_type(t_token_type type)
{
	return (type == TK_WORD || type == TK_REDIR_INPUT || type == TK_REDIR_OUTPUT
		|| type == TK_APPEND || type == TK_HEREDOC);
}

int	fill_args(t_cmd *cmd, t_token **token_list, int arg_count)
{
	int	i;

	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return (0);
	i = 0;
	while (*token_list && is_valid_token_type((*token_list)->type))
	{
		cmd->args[i] = ft_strdup((*token_list)->token);
		if (!cmd->args[i])
			return (free_cmd(cmd, 0), 0);
		*token_list = (*token_list)->next;
		i++;
	}
	cmd->args[i] = NULL;
	return (1);
}

void	free_ast(t_ast *node, int flag_unlink_heredoc)
{
	if (!node)
		return ;
	if (node->right)
	{
		free_ast(node->right, flag_unlink_heredoc);
		node->right = NULL;
	}
	if (node->left)
	{
		free_ast(node->left, flag_unlink_heredoc);
		node->left = NULL;
	}
	if (node->cmd)
	{
		free_cmd(node->cmd, flag_unlink_heredoc);
		node->cmd = NULL;
	}
	free(node);
	node = NULL;
}
