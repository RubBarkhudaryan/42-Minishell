/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_maker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:52:28 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/13 00:22:34 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./tokenizer.h"

int	make_word_token(t_token **head, char *str, int i)
{
	int		j;
	char	quote;

	j = 0;
	while (str[i + j])
	{
		if (ft_is_word_part(str[i + j]))
			++j;
		else if (str[i + j] == '\'' || str[i + j] == '\"')
		{
			quote = str[i + j++];
			while (str[i + j])
			{
				if (str[i + j] == quote && str[i + j - 1] != '\\')
					break ;
				++j;
			}
			if (str[i + j] == quote)
				++j;
		}
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
