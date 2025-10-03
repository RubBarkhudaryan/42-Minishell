/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 15:45:25 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/10/02 19:58:52 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

void	free_ast(t_ast *node, int flag_unlink_heredoc)
{
	if (!node)
		return ;
	free_ast(node->right, flag_unlink_heredoc);
	free_ast(node->left, flag_unlink_heredoc);
	free_cmd(node->cmd, flag_unlink_heredoc);
	free(node);
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
		while (node->cmd->args && node->cmd->args[++i])
			printf("%s ", node->cmd->args[i]);
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

t_token	*find_matching_parenthesis(t_token *start)
{
	int		count;
	t_token	*current;

	count = 0;
	current = start;
	while (current != NULL)
	{
		if (current->token_type == TK_L_PARENTHESIS)
			count++;
		else if (current->token_type == TK_R_PARENTHESIS)
		{
			count--;
			if (count == 0)
				return (current);
		}
		current = current->next;
	}
	return (NULL);
}

t_ast	*pars_cmd(t_token **token_list, t_shell *shell)
{
	t_cmd	*cmd_tmp;
	t_ast	*node;
	t_ast	*subshell;
	t_token	*matching_paren;
	t_token	*saved_next;

	if (*token_list && (*token_list)->token_type == TK_L_PARENTHESIS)
	{
		matching_paren = find_matching_parenthesis(*token_list);
		if (!matching_paren)
			return (NULL);
		saved_next = matching_paren->next;
		matching_paren->next = NULL;
		*token_list = (*token_list)->next;
		subshell = build_ast(token_list, shell);
		matching_paren->next = saved_next;
		*token_list = matching_paren->next;
		node = malloc(sizeof(t_ast));
		if (!node)
			return (free_shell(shell, 0), ft_putstr_fd("malloc failure", 2), NULL);
		node->cmd = NULL;
		node->left = subshell;
		node->right = NULL;
		node->type = NODE_SUBSHELL;
		return (node);
	}
	cmd_tmp = give_token_for_cmd(token_list, shell);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (free_shell(shell, 0), ft_putstr_fd("malloc failure", 2), NULL);
	node->type = NODE_COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->cmd = cmd_tmp;
	if (!node->cmd)
		return (free_shell(shell, 0), ft_putstr_fd("malloc failure", 2), NULL);
	return (node);
}

t_ast	*pars_pipe(t_token **token_list, t_shell *shell)
{
	t_ast	*left;
	t_ast	*right;
	t_ast	*node;

	left = pars_cmd(token_list, shell);
	while (*token_list && (*token_list)->token_type == TK_PIPE)
	{
		*token_list = (*token_list)->next;
		right = pars_cmd(token_list, shell);
		node = malloc(sizeof(t_ast));
		if (!node)
			return (free_shell(shell, 0), ft_putstr_fd("malloc failure", 2), NULL);
		node->left = left;
		node->right = right;
		node->cmd = NULL;
		node->type = NODE_PIPE;
		left = node;
	}
	return (left);
}

t_ast	*pars_ast(t_token **token_list, t_shell *shell)
{
	t_ast			*left;
	t_ast			*right;
	t_token_type	type;
	t_ast			*node;

	if (!(*token_list) || !token_list)
		return (NULL);
	left = pars_pipe(token_list, shell);
	while (*token_list && ((*token_list)->token_type == TK_OR
			|| (*token_list)->token_type == TK_AND))
	{
		type = (*token_list)->token_type;
		*token_list = (*token_list)->next;
		right = pars_pipe(token_list, shell);
		node = malloc(sizeof(t_ast));
		if (!node)
			return (free_shell(shell, 0), ft_putstr_fd("malloc failure", 2), NULL);
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

t_ast	*build_ast(t_token **token_list, t_shell *shell)
{
	return (pars_ast(token_list, shell));
}
