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

#include "tokenizer.h"

static char	*expand_dollar_token(char *token, t_env *env)
{
	t_env	*env_node;
	char	*expanded;
	char	*key;
	int		i;
	int		j;

	expanded = ft_strdup("");
	if (!token || !(*token) || !env || !expanded)
		return (NULL);
	i = 0;
	while (token[i])
	{
		j = 1;
		while (token[i + j] && ft_isalpha(token[i + j]))
			++j;
		key = ft_substr(token, i + 1, j - 1);
		if (!key)
			return (ft_strdup(""));
		env_node = search_node(key, env);
		if (!env_node || !env_node->value)
			return (free(key), ft_strdup(""));
		expanded = ft_strjoin(expanded, env_node->value);
		i += j;
	}
	return (free(key), expanded);
}

static char	*expand_nested_quote(char *token, int type, t_env *env)
{
	char	*clean_token;
	char	*dollar_tk;
	char	*temp;
	char	*tk;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = -1;
	tk = ft_substr(token, 1, ft_strlen(token) - 2);
	clean_token = (char *)malloc(ft_strlen(token) + 1);
	if (!tk || !clean_token)
		return (NULL);
	while (tk[i])
	{
		if ((tk[i] == '\\' && tk[i + 1] == '\"' && type == TK_DOUBLE_QUOTE) ||
			(tk[i] == '\\' && tk[i + 1] == '\'' && type == TK_SINGLE_QUOTE))
		{
			clean_token[++j] = tk[i + 1];
			i += 2;
		}
		if (tk[i] == '$' && ft_isalpha(tk[i + 1]) && type != TK_SINGLE_QUOTE)
		{
			k = i + 1;
			while (ft_isalpha(tk[k]))
				++k;
			dollar_tk = expand_dollar_token(ft_substr(tk, i, k - i), env);
			temp = ft_strdup(clean_token);
			free(clean_token);
			if (!dollar_tk)
				clean_token = ft_strjoin(clean_token, "");
			else
			{
				clean_token = ft_strjoin(temp, dollar_tk);
				j += ft_strlen(dollar_tk);
				free(dollar_tk);
			}
			free(temp);
			i = k;
		}
		else
			clean_token[++j] = tk[i++];
	}
	return (free(tk), clean_token[ft_strlen(clean_token)] = '\0', clean_token);
}

void	expand_tokens(t_token **token_list, t_env *env)
{
	t_token	*token;
	char	*tmp_tk;

	token = *token_list;
	while (token)
	{
		if (token->token_type == TK_DOUBLE_QUOTE ||
			token->token_type == TK_SINGLE_QUOTE)
		{
			tmp_tk = expand_nested_quote(token->token, token->token_type, env);
			if (!tmp_tk)
				return ;
			free(token->token);
			token->token = ft_strdup(tmp_tk);
			free(tmp_tk);
		}
		else if (token->token_type == TK_DOLLAR)
		{
			tmp_tk = expand_dollar_token(token->token, env);
			if (!tmp_tk)
				return ;
			free(token->token);
			token->token = ft_strdup(tmp_tk);
			free(tmp_tk);
		}
		token = token->next;
	}
}
