/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:08:37 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/10/25 20:09:20 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

int	analyze_command(t_ast *node)
{
	if (!node)
		return (1);
	if (node->type != NODE_COMMAND)
		return (1);
	if (!node->cmd || !node->cmd->args || !node->cmd->args[0])
	{
		if (!node->cmd->redirs_cmd)
		{
			ft_putstr_fd("minishell: syntax error empty command\n", 2);
			return (0);
		}
	}
	return (1);
}

int	analyze_pipe(t_ast *node)
{
	if (!node)
		return (1);
	if (node->type != NODE_PIPE)
		return (1);
	if (!node->left || !node->right)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	return (syntax_analyze(node->left) && syntax_analyze(node->right));
}

int	analyze_logical(t_ast *node)
{
	if (!node)
		return (1);
	if (node->type != NODE_AND && node->type != NODE_OR)
		return (1);
	if (!node->left || !node->right)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (node->type == NODE_AND)
			ft_putstr_fd("&&'\n", 2);
		else if (node->type == NODE_OR)
			ft_putstr_fd("||'\n", 2);
		return (0);
	}
	return (syntax_analyze(node->left) && syntax_analyze(node->right));
}

int	syntax_analyze(t_ast *ast)
{
	t_ast	*node;

	if (!ast)
		return (0);
	node = ast;
	if (node->type == NODE_COMMAND)
		return (analyze_command(node));
	if (node->type == NODE_PIPE)
		return (analyze_pipe(node));
	else if (node->type == NODE_OR || node->type == NODE_AND)
		return (analyze_logical(node));
	else if (node->type == NODE_SUBSHELL)
		return (syntax_analyze(node->left));
	return (1);
}
