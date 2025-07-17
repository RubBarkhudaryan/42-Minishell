/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:52:28 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/07/17 18:21:16 by rbarkhud         ###   ########.fr       */
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
	add_token(head, ft_substr(str, i, j));
	return (i + j);
}

int	make_word_token(t_token **head, char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j])
	{
		if (ft_isalpha(str[i + j]) || ft_inset(str[i + j],
				"^-_*.$+=\\0123456789"))
			++j;
		else
			break ;
	}
	add_token(head, ft_substr(str, i, j));
	return (i + j);
}

int	make_specials_token(t_token **head, char *str, int i)
{
	int	j;

	j = 1;
	while (str[i + j])
	{
		if (ft_inset(str[i + j], "|&<>();"))
			++j;
		else
			break ;
	}
	add_token(head, ft_substr(str, i, j));
	return (i + j);
}
