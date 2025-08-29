/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:56:45 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/29 17:11:13 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static int	ft_is_word_part(char c)
{
	return (ft_isalnum(c) || ft_inset(c, "!@#$%^*-_+=~`;.?,{}[]\\/"));
}

t_token	*tokenize(char *str)
{
	int		i;
	t_token	*head;

	i = 0;
	head = NULL;
	if (!str || !(*str))
		return (NULL);
	while (str[i])
	{
		while (str[i] && ft_isspace(str[i]))
			++i;
		if (str[i] == '\'' || str[i] == '\"')
			i = make_quoted_token(&head, str, i);
		else if (ft_is_word_part(str[i]))
			i = make_word_token(&head, str, i);
		else if (ft_inset(str[i], "|&<>"))
			i = make_specials_token(&head, str, i);
		else if (ft_inset(str[i], "()"))
			i = parse_subshell(&head, str, i);
		else
			++i;
		if (i == -1)
			return (free_token_list(head), NULL);
	}
	return (head);
}
