/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:39:05 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/09 13:25:33 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

int	is_redir(t_token *token)
{
	if (!token)
		return (0);
	return ((token->token_type >= TK_REDIR_INPUT
			&& token->token_type <= TK_HEREDOC));
}

int	validate_parenthesis(t_token *token_list)
{
	int count_paren;

	count_paren = 0;
	while (token_list)
	{
		if (token_list->token_type == TK_L_PARENTHESIS)
			count_paren++;
		if (token_list->token_type == TK_R_PARENTHESIS)
			count_paren--;
		token_list = token_list->next;
	}
	if (count_paren == 0)
		return (0);
	return (1);
}
