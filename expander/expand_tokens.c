/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 15:34:56 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/25 15:34:56 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	change_val(char **str1, char **str2)
{
	free(*str1);
	*str1 = ft_strdup(*str2);
	free(*str2);
}

char	*join_args(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*join;

	if (!str1 && str2)
		return (ft_strdup(str2));
	if (str1 && !str2)
		return (ft_strdup(str1));
	if (!str1 && !str2)
		return (NULL);
	join = (char *)malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (!join)
		return (NULL);
	i = -1;
	j = -1;
	while (str1[++i])
		join[i] = str1[i];
	while (str2[++j])
		join[i + j] = str2[j];
	join[i + j] = '\0';
	return (join);
}

void	expand_tokens(t_token **token_list, t_env *env)
{
	t_token	*token;
	char	*tmp_tk;

	token = *token_list;
	while (token)
	{
		if (token->token_type == TK_DOUBLE_QUOTE
			|| token->token_type == TK_SINGLE_QUOTE)
		{
			tmp_tk = expand_nested_quote(token->token, token->token_type, env);
			if (!tmp_tk)
				return ;
			change_val(&token->token, &tmp_tk);
		}
		else if (token->token_type == TK_DOLLAR)
		{
			tmp_tk = expand_dollar_token(token->token, env);
			if (!tmp_tk)
				return ;
			change_val(&token->token, &tmp_tk);
			token->token_type = TK_WORD;
		}
		token = token->next;
	}
}
