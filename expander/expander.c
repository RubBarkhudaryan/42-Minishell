/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:43:30 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/23 17:49:59 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

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
	int		is_here_doc;

	token = *token_list;
	is_here_doc = 0;
	while (token)
	{
		if (token->token_type == TK_HEREDOC)
			is_here_doc = 1;
		if (token->token_type == TK_WORD)
		{
			tmp_tk = expand_nested_quote(token->token, env, is_here_doc);
			if (!tmp_tk)
				return ;
			change_val(&token->token, &tmp_tk);
		}
		else if (is_here_doc && token->token_type == TK_WORD)
			is_here_doc = 0;
		token = token->next;
	}
}
