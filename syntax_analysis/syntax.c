/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:08:37 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/10/04 14:10:37 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

// int	analyze_pipe(t_ast *ast)
// {
// 	t_ast	*node;

// 	if (!ast)
// 		return (0);
// 	node = ast;
// 	if (analyze_cmd(node->left))
// }

// int	syntax_analyze(t_ast *ast)
// {
// 	t_ast	*node;

// 	if (!ast)
// 		return (0);
// 	node = ast;
// 	if (node->type == NODE_PIPE)
// 	{
// 		if (analyze_pipe(node->left) && analyze_pipe(node->right))
// 			return (1);
// 	}
// }

// int	analyze(t_token *token_list)
// {
// 	t_token	*token;

// 	token = token_list;
// 	if (!token)
// 		return (0);
// 	if (is_operator(token))
// 		return (0);
// 	while (token)
// 	{
// 		if (token->token_type == TK_ERROR)
// 			return (0);
// 		if (!check_syntax_errors(token))
// 			return (0);
// 		token = token->next;
// 	}
// 	return (1);
// }
