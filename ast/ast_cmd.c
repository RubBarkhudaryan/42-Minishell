/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:18:35 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/24 01:04:07 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

t_ast	*handle_subshell(t_token **token_list, t_shell *shell)
{
	t_ast	*node;
	t_ast	*subshell;
	t_token	*matching_paren;
	t_token	*saved_next;

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
		return (ft_putstr_fd("subshell -> malloc failure", 2), NULL);
	node->cmd = give_token_for_cmd(token_list, shell);
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
