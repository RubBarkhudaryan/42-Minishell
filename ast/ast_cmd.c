/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:18:35 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/10 19:45:56 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

t_ast	*handle_subshell(t_token **token_list, t_shell *shell)
{
	t_ast	*node;
	t_ast	*subshell;

	*token_list = (*token_list)->next;
	subshell = build_ast(token_list, shell);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (ft_putstr_fd("subshell -> malloc failure", 2), NULL);
	if (*token_list)
		*token_list = (*token_list)->next;
	node->cmd = give_token_for_cmd(token_list, 1, shell);
	if (!node->cmd)
		set_cmd(node);
	node->left = subshell;
	if (node->left->cmd)
		node->left->cmd->in_subshell = true;
	node->right = NULL;
	node->type = NODE_SUBSHELL;
	return (node);
}

t_ast	*handle_regular_command(t_token **token_list,
		bool in_subshell, t_shell *shell)
{
	t_cmd	*cmd_tmp;
	t_ast	*node;

	cmd_tmp = give_token_for_cmd(token_list, in_subshell, shell);
	node = malloc(sizeof(t_ast));
	if (!node)
		return (ft_putstr_fd("node in cmd -> malloc failure1\n", 2), NULL);
	node->type = NODE_COMMAND;
	node->left = NULL;
	node->right = NULL;
	node->cmd = cmd_tmp;
	return (node);
}
