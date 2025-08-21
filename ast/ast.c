/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:45:25 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/20 11:46:47 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

t_ast	*pars_cmd(t_token **token_list)
{
	t_ast	*node;
	t_ast	*subshell;

	if (*token_list && (*token_list)->token_type == TK_L_PARENTHESIS)
	{
		*token_list = (*token_list)->next;
		subshell = build_ast(&*token_list);
		if (*token_list)
			*token_list = (*token_list)->next;
		if (*token_list && (*token_list)->token_type != TK_R_PARENTHESIS)
			return (NULL);
		node = malloc(sizeof(t_ast));
		if (!node)
			return (NULL); // malloc	fail
		node->cmd = NULL;
		node->left = subshell;
		node->right = NULL;
		node->type = NODE_SUBSHELL;
		return (node);
	}
	node = malloc(sizeof(t_ast));
	if (!node)
		return (NULL); // malloc	fail
	node->type = NODE_COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->cmd = (*token_list);
	while (*token_list && ((*token_list)->token_type == TK_WORD
			|| (*token_list)->token_type == TK_SINGLE_QUOTE
			|| (*token_list)->token_type == TK_DOUBLE_QUOTE
			|| (*token_list)->token_type == TK_DOLLAR
			|| (*token_list)->token_type == TK_HEREDOC
			|| (*token_list)->token_type == TK_REDIR_INPUT
			|| (*token_list)->token_type == TK_REDIR_OUTPUT
			|| (*token_list)->token_type == TK_APPEND))
		(*token_list) = (*token_list)->next;
	return (node);
}

t_ast	*pars_pipe(t_token **token_list)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	left = pars_cmd(token_list);
	while (*token_list && (*token_list)->token_type == TK_PIPE)
	{
		*token_list = (*token_list)->next;
		right = pars_cmd(&(*token_list));
		node = malloc(sizeof(t_ast));
		if (!node)
			return (NULL); // malloc	fail
		node->left = left;
		node->right = right;
		node->cmd = NULL;
		node->type = NODE_PIPE;
		left = node;
	}
	return (left);
}

t_ast	*pars_ast(t_token **token_list)
{
	t_ast			*left;
	t_ast			*right;
	t_token_type	type;
	t_ast			*node;

	if (!(*token_list) || !token_list)
		return (NULL);
	left = pars_pipe(token_list);
	while (*token_list && ((*token_list)->token_type == TK_OR
			|| (*token_list)->token_type == TK_AND))
	{
		type = (*token_list)->token_type;
		*token_list = (*token_list)->next;
		right = pars_pipe(token_list);
		node = malloc(sizeof(t_ast));
		if (!node)
			return (NULL); // malloc	fail
		node->left = left;
		node->right = right;
		node->cmd = NULL;
		if (type == TK_OR)
			node->type = NODE_OR;
		else
			node->type = NODE_AND;
		left = node;
	}
	return (left);
}

t_ast	*build_ast(t_token **token_list)
{
	return (pars_ast(token_list));
}
