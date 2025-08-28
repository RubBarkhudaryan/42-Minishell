/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:12:20 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/26 16:04:30 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	make_subshell_token(t_token **head, char *str, int i)
{
	int	new_i;

	while (ft_isspace(str[i]))
		++i;
	if (str[i] == '\'' || str[i] == '\"')
	{
		new_i = make_quoted_token(head, str, i);
		if (new_i != i)
			return (new_i);
	}
	else if (ft_inset(str[i], "|&<>"))
	{
		new_i = make_specials_token(head, str, i);
		if (new_i != i)
			return (new_i);
	}
	else
	{
		new_i = make_word_token(head, str, i);
		if (new_i != i)
			return (new_i);
	}
	return (i);
}

int	parse_subshell(t_token **head, char *str, int i)
{
	int		l_count;
	int		r_count;
	int		is_alpha;

	l_count = 0;
	r_count = 0;
	is_alpha = 0;
	while (str[i])
	{
		if (str[i] == '(' || str[i] == ')')
		{
			add_token(head, ft_substr(str, i, 1));
			if (str[i] == '(')
				++l_count;
			else
				++r_count;
		}
		else if (!ft_inset(str[i], "()"))
		{
			is_alpha = 1;
			i = make_subshell_token(head, str, i);
			continue ;
		}
		++i;
	}
	if (l_count == r_count && is_alpha)
		return (i);
	return (-1);
}
