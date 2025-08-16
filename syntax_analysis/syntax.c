/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:08:37 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/16 23:15:31 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"

int	analyze(t_token *token_list)
{
	t_token	*token;

	token = token_list;
	if (!token)
		return (0);
	if (is_operator(token))
		return (0);
	while (token)
	{
		if (token->token_type == TK_ERROR)
			return (0);
		if (!check_syntax_errors(token))
			return (0);
		token = token->next;
	}
	return (1);
}
