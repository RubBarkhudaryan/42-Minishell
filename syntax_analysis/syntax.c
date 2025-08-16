/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 16:08:37 by rbarkhud          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/15 16:57:12 by rbarkhud         ###   ########.fr       */
=======
/*   Updated: 2025/08/12 16:40:06 by apatvaka         ###   ########.fr       */
>>>>>>> execute
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
