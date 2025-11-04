/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:18:35 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/04 20:47:18 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

t_ast	*handle_subshell(t_token **token_list, t_shell *shell)
{
	t_ast	*node;
	t_ast	*subshell;

	*token_list = (*token_list)->next;
	subshell = build_ast(token_list, shell);
	// while ((*token_list) && ((*token_list)->token_type != TK_R_PARENTHESIS
	// 		|| (*token_list)->token_type != TK_OR
	// 		|| (*token_list)->token_type != TK_AND
	// 		|| (*token_list)->token_type != TK_PIPE))
	// 	(*token_list) = (*token_list)->next;
	node = malloc(sizeof(t_ast));
	if (!node)
		return (ft_putstr_fd("subshell -> malloc failure", 2), NULL);
	node->cmd = give_token_for_cmd(token_list, shell);
	if (*token_list)
		*token_list = (*token_list)->next;
	if (!node->cmd)
		set_cmd(node);
	node->left = subshell;
	node->right = NULL;
	node->type = NODE_SUBSHELL;
	return (node);
}

t_ast	*handle_regular_command(t_token **token_list, t_shell *shell)
{
	t_cmd	*cmd_tmp;
	t_ast	*node;

	cmd_tmp = give_token_for_cmd(token_list, shell);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (ft_putstr_fd("node in cmd -> malloc failure\n", 2), NULL);
	node->type = NODE_COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->cmd = cmd_tmp;
	if (!node->cmd)
		return (free(node), ft_putstr_fd("cmd -> malloc failure\n", 2), NULL);
	return (node);
}
