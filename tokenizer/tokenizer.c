/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:56:45 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/01 12:59:53 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*tokenize(char *str)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	while (str[i])
	{
		while (str[i] && tk_isspace(str[i]))
			++i;
		if (str[i] == '\'' || str[i] == '\"')
			i = make_quoted_token(&head, str, i);
		else if (tk_isalpha(str[i]) || tk_inset(str[i],
				"!@#$%^*-_+=~`;.?,{}[]\\/0123456789"))
			i = make_word_token(&head, str, i);
		else if (tk_inset(str[i], "|&<>()"))
			i = make_specials_token(&head, str, i);
		else
			++i;
	}
	return (head);
}
