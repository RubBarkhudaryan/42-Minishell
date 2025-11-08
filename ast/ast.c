/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:45:25 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/08 15:17:53 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

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

t_ast	*parse_cmd(t_token **token_list, t_shell *shell)
{
	if (*token_list && (*token_list)->token_type == TK_L_PARENTHESIS)
		return (handle_subshell(token_list, shell));
	else
		return (handle_regular_command(token_list, shell));
}

t_ast	*parse_pipe(t_token **token_list, t_shell *shell)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	left = parse_cmd(token_list, shell);
	if (*token_list)
		while (*token_list && (*token_list)->token_type == TK_PIPE)
		{
			*token_list = (*token_list)->next;
			right = parse_cmd(token_list, shell);
			node = malloc(sizeof(t_ast));
			if (!node)
				return (ft_putstr_fd("pipe -> malloc failure\n", 2), NULL);
			node->left = left;
			node->right = right;
			node->cmd = NULL;
			node->type = NODE_PIPE;
			left = node;
		}
	return (left);
}

t_ast	*parse_ast(t_token **token_list, t_shell *shell)
{
	t_ast			*left;
	t_ast			*right;
	t_token_type	type;
	t_ast			*node;

	if (!(*token_list) || !token_list)
		return (NULL);
	left = parse_pipe(token_list, shell);
	while (*token_list && ((*token_list)->token_type == TK_OR
			|| (*token_list)->token_type == TK_AND))
	{
		type = (*token_list)->token_type;
		*token_list = (*token_list)->next;
		right = parse_pipe(token_list, shell);
		node = malloc(sizeof(t_ast));
		if (!node)
			return (ft_putstr_fd("ast -> malloc failure\n", 2), NULL);
		node->left = left;
		node->right = right;
		set_type(node, type);
		node->cmd = NULL;
		left = node;
	}
	return (left);
}

t_ast	*build_ast(t_token **token_list, t_shell *shell)
{
	return (parse_ast(token_list, shell));
}

void	print_ast(t_ast *node, int level)
{
	int	i;

	if (!node)
		return ;
	for (int i = 0; i < level; i++)
		printf("  ");
	switch (node->type)
	{
	case NODE_COMMAND:
		printf("COMMAND: ");
		i = -1;
		while (node->cmd && node->cmd->args && node->cmd->args[++i])
			printf("%s ", node->cmd->args[i]);
		if (node->cmd)
			print_redir_cmd(node->cmd->redirs_cmd);
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
