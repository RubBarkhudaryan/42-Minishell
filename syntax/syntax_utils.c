/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:39:05 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/15 20:24:18 by rbarkhud         ###   ########.fr       */
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
	int	count_paren;

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
	ft_putstr_fd("minishell: syntax error unexpected token near `)'\n", 2);
	return (1);
}

int	check_quoted_str(t_token *head)
{
	t_token	*list;

	if (!head)
		return (0);
	list = head;
	while (list)
	{
		if (list->token_type == TK_ERROR)
		{
			ft_putstr_fd("minishell: syntax error unexpected token near `", 2);
			ft_putstr_fd(list->token, 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
		list = list->next;
	}
	return (0);
}
