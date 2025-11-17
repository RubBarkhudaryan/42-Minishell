/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:45:25 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/17 15:51:41 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

t_ast *create_ast_node(t_ast *left, t_ast *right, int type, t_cmd *cmd)
{
	t_ast *node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (ft_putstr_fd("minishell: ast node malloc failure\n", 2), NULL);
	if (type == TK_OR)
		node->type = NODE_OR;
	else if (type == TK_AND)
		node->type = NODE_AND;
	else
		node->type = type;
	node->left = left;
	node->right = right;
	node->cmd = cmd;
	return (node);
}

void throw_error(char *target)
{
	ft_putstr_fd(ERR_MSG, 2);
	ft_putstr_fd(target, 2);
	ft_putstr_fd("'\n", 2);
}

void free_ast(t_ast *node, int flag_unlink_heredoc)
{
	if (!node)
		return;
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

t_ast *parse_cmd(t_token **token_list, t_shell *shell)
{
	if (*token_list && (*token_list)->type == TK_L_PARENTHESIS)
		return (parse_subshell(token_list, shell));
	else
		return (parse_regular_command(token_list, shell));
}

t_ast *parse_pipe(t_token **list, t_shell *shell)
{
	t_ast *left;
	t_ast *right;
	t_ast *node;

	left = parse_cmd(list, shell);
	if (!left)
		return (NULL);
	while (*list && (*list)->type == TK_PIPE)
	{
		*list = (*list)->next;
		right = parse_cmd(list, shell);
		if (!right)
			return (free_ast(left, 0), NULL);
		node = create_ast_node(left, right, NODE_PIPE, NULL);
		if (!node)
			return (free_ast(left, 0), free_ast(right, 0), NULL);
		left = node;
	}
	return (left);
}

t_ast *parse_ast(t_token **list, t_shell *shell)
{
	t_ast *left;
	t_ast *right;
	t_token_type type;
	t_ast *node;

	if (!(*list) || !list)
		return (printf("Hello\n"),NULL);
	left = parse_pipe(list, shell);
	if (!left)
		return (NULL);
	while (*list && ((*list)->type == TK_OR || (*list)->type == TK_AND))
	{
		type = (*list)->type;
		*list = (*list)->next;
		right = parse_pipe(list, shell);
		if (!right)
			return (free_ast(left, 0), NULL);
		node = create_ast_node(left, right, type, NULL);
		if (!node)
			return (free_ast(left, 0), free_ast(right, 0), NULL);
		left = node;
	}
	return (left);
}

t_ast *build_ast(t_token **list, t_shell *shell)
{
	t_ast	*res;

	res = parse_ast(list, shell);
	if (!res)
	{
		if (!(*list))
			printf("error\n");
		else
			throw_error((*list)->token);
		shell->last_exit_code = 2;
		return (free_ast(res, 0), NULL);
	}
	return (res);
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
