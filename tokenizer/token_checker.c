/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 22:21:01 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/24 17:17:05 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer.h"

int	ft_is_word_part(char c)
{
	return (ft_isalnum(c) || ft_inset(c, "!@#$%^*-_+=~`:;.?,{}[]\\/"));
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}

int	ft_inset(char c, char *set)
{
	int	i;

	if (!set)
		return (0);
	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		++i;
	}
	return (0);
}

int	check_quoted_str(t_token *head)
{
	t_token	*list;

	if (!head)
		return (0);
	list = head;
	while (list)
	{
		if (check_quoted_token_type(list->token) == TK_ERROR)
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
