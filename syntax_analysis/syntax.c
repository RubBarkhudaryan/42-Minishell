/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:08:37 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/05 18:05:09 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "syntax.h"
#include <errno.h>

int	analyze(t_token *token_list)
{
	t_token	*token;

	if (!token_list)
		return (0);
	token = token_list;
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
