/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 18:18:35 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/17 02:24:50 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

// t_ast	*parse_subshell(t_token **list, t_shell *shell)
// {
// 	t_ast	*node;
// 	t_ast	*subshell;

// 	*list = (*list)->next;
// 	subshell = parse_ast(list, shell);
// 	if (!subshell)
// 		return (NULL);
// 	if (*list && (*list)->type == TK_R_PARENTHESIS)
// 		*list = (*list)->next;
// 	if (*list && ((*list)->type == TK_WORD || (*list)->type == TK_ERROR))
// 	{
// 		shell->last_exit_code = 2;
// 		return (free_ast(subshell, 1), NULL);
// 	}
// 	node = create_ast_node(subshell, NULL, NODE_SUBSHELL,
// 			give_token_for_cmd(list, 1, shell));
// 	if (!node)
// 		return (free_ast(subshell, 1), NULL);
// 	if (!node->cmd)
// 		node = init_cmd();
// 	shell->in_subshell = true;
// 	return (node);
// }

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
	int		type;

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
	subshell->cmd = init_cmd();
	if (!subshell->cmd)
		return (free_ast(subshell, 1), NULL);
	while((*list) && is_redir(*list))
	{
		type = (*list)->type;
		(*list) = (*list)->next;
		if (!(*list))
			return (free_ast(subshell, 1), NULL);
		add_redir(subshell->cmd->redirs_cmd, init_redir(type, (*list)->token));
		(*list) = (*list)->next;
	}
	return (subshell);
}
