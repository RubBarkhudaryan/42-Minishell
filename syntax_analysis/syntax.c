/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:08:37 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/10/23 00:00:00 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

static int analyze_command(t_ast *node)
{
	if (!node || node->type != NODE_COMMAND)
		return (1);
	/* Accept commands that are only redirections; just ensure cmd exists */
	if (!node->cmd)
	{
		ft_putstr_fd("minishell: syntax error empty command\n", 2);
		return (0);
	}
	return (1);
}

static int analyze_pipe(t_ast *node)
{
	if (!node || node->type != NODE_PIPE)
		return (1);
	if (!node->left || !node->right)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (0);
	}
	return (syntax_analyze(node->left) && syntax_analyze(node->right));
}

static int analyze_logical(t_ast *node)
{
	if (!node || (node->type != NODE_AND && node->type != NODE_OR))
		return (1);
	if (!node->left || !node->right)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (node->type == NODE_AND)
			ft_putstr_fd("&&'\n", 2);
		else
			ft_putstr_fd("||'\n", 2);
		return (0);
	}
	return (syntax_analyze(node->left) && syntax_analyze(node->right));
}

int syntax_analyze(t_ast *ast)
{
	if (!ast)
		return (0);
	if (ast->type == NODE_COMMAND)
		return (analyze_command(ast));
	if (ast->type == NODE_PIPE)
		return (analyze_pipe(ast));
	if (ast->type == NODE_AND || ast->type == NODE_OR)
		return (analyze_logical(ast));
	if (ast->type == NODE_SUBSHELL)
		return (ast->left ? syntax_analyze(ast->left) : 1);
	return (1);
}
