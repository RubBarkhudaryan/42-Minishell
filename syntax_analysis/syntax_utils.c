/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:39:05 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/02 16:04:56 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

int	is_operator(t_token *token)
{
	return (token->token_type >= TK_PIPE && token->token_type <= TK_AND);
}

int	is_redir(t_token *token)
{
	return (token->token_type >= TK_APPEND
		&& token->token_type <= TK_REDIR_OUTPUT);
}

int	check_syntax_errors(t_token *token)
{
	if (!token->next)
		return (1);
	if (is_operator(token) && is_operator(token->next))
		return (0);
	if (is_redir(token) && is_operator(token->next))
		return (0);
	if (is_redir(token) && (!token->next || token->next->token_type != TK_WORD))
		return (0);
	if (token->token_type == TK_L_PARENTHESIS && is_operator(token->next))
		return (0);
	if (is_operator(token) && token->next->token_type == TK_R_PARENTHESIS)
		return (0);
	if (is_operator(token) && token->next->token_type == TK_R_PARENTHESIS)
		return (0);
	if (token->token_type == TK_WORD
		&& token->next->token_type == TK_L_PARENTHESIS)
		return (0);
	if (token->token_type == TK_R_PARENTHESIS
		&& token->next->token_type == TK_WORD)
		return (0);
	return (1);
}
