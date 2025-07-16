/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:31:26 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/16 16:59:17 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parsing.h"

static int	is_operator(char *str)
{
	return (*str == '|' || *str == '>' || *str == '<');
}

t_token_type	token_tupe_search(char *str, int *len)
{
	if (str[0] == '>' && str[1] == '>')
		return (*len = 2, TOKEN_APPEND);
	if (str[0] == '<' && str[1] == '<')
		return (*len = 2, TOKEN_HEREDOC);
	if (str[0] == '|')
		return (*len = 1, TOKEN_PIPE);
	if (str[0] == '<')
		return (*len = 1, TOKEN_REDIRECT_IN);
	if (str[0] == '>')
		return (*len = 1, TOKEN_REDIRECT_OUT);
	return (*len = 0, 0);
}
char	*tokenized(char *str)
{
	t_token_type	type;
	char			*tmp;
	t_token			*ret;
	int				i;
	int				len;

	i = -1;
	len = 0;
	while (str[++i])
	{
		if (is_space(&str[i]))
			++i;
		else if (is_operator(&str[i]))
		{
			type = token_type_search(&str[i], len);
			tmp = ft_substr(&str[i], i, &len);
			if (!tmp)
				return (NULL); //????????
			lst_add_back(&ret, tmp, type);
		}
		else
		{
		}
	}
	return (NULL);
}
