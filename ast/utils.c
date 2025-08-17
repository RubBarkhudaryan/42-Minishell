/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 12:04:41 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/17 17:05:16 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

void	free_ast(t_ast *node)
{
	if (!node)
		return ;
	free_token_list(&node->cmd);
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

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
		while (t && node->type == NODE_COMMAND && (t->token_type == TK_WORD
				|| t->token_type == TK_SINGLE_QUOTE
				|| t->token_type == TK_DOUBLE_QUOTE
				|| t->token_type == TK_DOLLAR || t->token_type == TK_HEREDOC
				|| t->token_type == TK_REDIR_INPUT
				|| t->token_type == TK_REDIR_OUTPUT
				|| t->token_type == TK_APPEND))
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
