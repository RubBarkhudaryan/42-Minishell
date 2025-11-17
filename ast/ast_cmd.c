/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:18:35 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/17 16:00:27 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

t_ast	*parse_regular_command(t_token **list, t_shell *shell)
{
	t_cmd	*cmd_tmp;
	t_ast	*node;

	cmd_tmp = make_cmd(list, shell);
	if (!cmd_tmp)
		return (NULL);
	node = create_ast_node(NULL, NULL, NODE_COMMAND, cmd_tmp);
	if (!node)
		return (free_cmd(cmd_tmp, 1), NULL);
	return (node);
}

t_ast	*parse_subshell(t_token **list, t_shell *shell)
{
	t_ast	*subshell;

	// int		type;
	subshell = create_ast_node(NULL, NULL, NODE_SUBSHELL, NULL);
	if (!subshell)
		return (NULL);
	(*list) = (*list)->next;
	subshell->left = parse_ast(list, shell);
	if (!subshell->left)
		return (free(subshell), NULL);
	if (!(*list) || (*list)->type != TK_R_PARENTHESIS)
		return (free_ast(subshell, 1), NULL);
	(*list) = (*list)->next;
	subshell->cmd = make_cmd(list, shell); // init_cmd
	if (!subshell->cmd)
		return (free_ast(subshell, 1), NULL);
	return (subshell);
}

// while((*list) && is_redir(*list))
// {
// 	type = (*list)->type;
// 	(*list) = (*list)->next;
// 	if (!(*list))
// 		return (free_ast(subshell, 1), NULL);
// 	add_redir(subshell->cmd->redirs_cmd, init_redir(type, (*list)->token));
// 	(*list) = (*list)->next;
// }
