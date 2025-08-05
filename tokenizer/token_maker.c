/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:52:28 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/05 18:13:40 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer.h"

int	make_quoted_token(t_token **head, char *str, int i)
{
	int		j;
	char	quote;

	j = 1;
	quote = str[i];
	while (str[i + j])
	{
		if (str[i + j] == quote && str[i + (j - 1)] != '\\')
			break ;
		++j;
	}
	if (str[i + j] == quote)
		++j;
	add_token(head, tk_substr(str, i, j));
	return (i + j);
}

int	make_word_token(t_token **head, char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j])
	{
		if (tk_isalpha(str[i + j]) || tk_inset(str[i + j],
				"!@#$%^*-_+=~`;.?,{}[]\\/0123456789"))
			++j;
		else
			break ;
	}
	add_token(head, tk_substr(str, i, j));
	return (i + j);
}

int	make_specials_token(t_token **head, char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j])
	{
		if (tk_inset(str[i + j], "|&<>();"))
			++j;
		else
			break ;
	}
	add_token(head, tk_substr(str, i, j));
	return (i + j);
}
