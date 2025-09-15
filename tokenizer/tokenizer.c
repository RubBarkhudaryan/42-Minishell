/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:56:45 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/04 19:51:41 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

int	ft_is_word_part(char c)
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
		if (ft_is_word_part(str[i]) || str[i] == '\'' || str[i] == '\"')
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
