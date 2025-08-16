/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 19:56:45 by rbarkhud          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/06 15:08:35 by rbarkhud         ###   ########.fr       */
=======
/*   Updated: 2025/08/15 23:59:31 by apatvaka         ###   ########.fr       */
>>>>>>> execute
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

t_token	*tokenize(char *str)
{
	int		i;
	t_token	*head;

	i = -1;
	head = NULL;
	while (str[++i])
	{
		while (str[i] && ft_isspace(str[i]))
			++i;
		if (str[i] == '\'' || str[i] == '\"')
			i = make_quoted_token(&head, str, i);
<<<<<<< HEAD
		else if (ft_isalpha(str[i]) || ft_inset(str[i],
=======
		else if (ft_isalpha(str[i]) || tk_inset(str[i],
>>>>>>> execute
				"!@#$%^*-_+=~`;.?,{}[]\\/0123456789"))
			i = make_word_token(&head, str, i);
		else if (ft_inset(str[i], "|&<>"))
			i = make_specials_token(&head, str, i);
		else if (ft_inset(str[i], "()"))
		{
			i = parse_subshell(&head, str, i);
			if (i == -1)
				return (free_token_list(&head), printf("NULL\n"), NULL);
		}
	}
	return (head);
}
