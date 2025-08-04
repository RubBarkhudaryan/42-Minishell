/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:45:25 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/04 17:41:29 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

void	print_ast(t_ast *node, int level)
{
	t_token	*t;

	if (!node)
		return ;
	for (int i = 0; i < level; i++)
		printf("  ");
	switch (node->type)
	{
	case NODE_COMMAND:
		printf("COMMAND: ");
		t = node->cmd;
		while (t && (node->type == NODE_COMMAND)
		{
			printf("%s ", t->token);
			t = t->next;
		}
		printf("\n");
		break ;
	case NODE_PIPE:
		printf("PIPE\n");
		break ;
	case NODE_AND:
		printf("AND\n");
		break ;
	case NODE_OR:
		printf("OR\n");
		break ;
	case NODE_SUBSHELL:
		printf("SUBSHELL\n");
		break ;
	}
	print_ast(node->left, level + 1);
	print_ast(node->right, level + 1);
}

t_ast	*pars_cmd(t_token **token_list)
{
	t_token	*token;
	t_ast	*node;
	t_ast	*subshell;

	token = *token_list;
	if (token && token == TK_L_PARENTHESIS)
	{
		token = token->next;
		subshell = build_ast(&token);
		token = token->next;
		// if (token == TK_R_PARENTHESIS)
			// return (NULL); // malloc	fail
		node = malloc(sizeof(t_ast));
		if (!node)
			return (NULL);
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
	node->cmd = token;
	while (token && token->token_type == TK_WORD)
		token = token->next;
	return (node);
}

t_ast	*pars_pipe(t_token **token_list)
{
	t_ast	*left;
	t_token	*token;
	t_ast	*right;
	t_ast	*node;

	token = *token_list;
	left = pars_cmd(&token);
	while (token && token->token_type == TK_PIPE)
	{
		token = token->next;
		right = pars_cmd(&token);
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
	t_token			*token;
	t_ast			*left;
	t_ast			*right;
	t_token_type	type;
	t_ast			*node;

	token = *token_list;
	if (!token || !token_list)
		return (NULL);
	left = pars_pipe(&token);
	while (token && (token->token_type == TK_OR || token->token_type == TK_AND))
	{
		type = token->token_type;
		token = token->next;
		right = pars_pipe(&token);
		node = malloc(sizeof(t_ast));
		if (!node)
			return (NULL); // malloc	fail
		node->left = left;
		node->right = right;
		node->cmd = NULL;
		if (node->type == TK_OR)
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
