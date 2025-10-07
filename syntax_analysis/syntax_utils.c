/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:39:05 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/10/05 17:21:54 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

int	is_operator(t_token *token)
{
	if (!token)
		return (0);
	return (token->token_type >= TK_PIPE && token->token_type <= TK_OR);
}

int	is_redir(t_token *token)
{
	if (!token)
		return (0);
	return ((token->token_type >= TK_REDIR_INPUT
			&& token->token_type <= TK_HEREDOC));
	// || token->token_type == TK_R_PARENTHESIS);
}

int	check_syntax_errors(t_token *token)
{
	if (token->token_type == TK_WORD && !token->next)
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
	if (token->token_type == TK_WORD
		&& token->next->token_type == TK_L_PARENTHESIS)
		return (0);
	if (token->token_type == TK_R_PARENTHESIS
		&& token->next->token_type == TK_WORD)
		return (0);
	return (1);
}
