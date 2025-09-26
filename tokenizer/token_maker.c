/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:52:28 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/27 01:46:34 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	quote_handler(char *str, int i)
{
	char	quote;

	quote = str[i];
	++i;
	while (str[i])
	{
		if (str[i] == quote && str[i - 1] != '\\')
			break ;
		++i;
	}
	if (str[i] == quote)
		++i;
	return (i);
}

int	make_word_token(t_token **head, char *str, int i)
{
	int		j;

	j = 0;
	while (str[i + j])
	{
		if (ft_is_word_part(str[i + j]))
			++j;
		else if (str[i + j] == '\'' || str[i + j] == '\"')
			j = quote_handler(str, i + j) - i;
		else
			break ;
	}
	if (j != 0)
		add_token(head, ft_substr(str, i, j));
	return (i + j);
}

int	make_specials_token(t_token **head, char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j])
	{
		if (ft_inset(str[i + j], "|&<>"))
			++j;
		else
			break ;
	}
	if (j != 0)
		add_token(head, ft_substr(str, i, j));
	return (i + j);
}
