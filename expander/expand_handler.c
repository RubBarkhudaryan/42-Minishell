/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:21:15 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/10/26 18:21:15 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"


char	*expand_dollar_token(char *token, t_shell *shell)
{
	t_env		*env_node;
	t_expand	exp;
	int			i;
	int			j;

	exp.res = ft_strdup("");
	if (!token || !(*token) || !shell->env || !exp.res)
		return (free(exp.res), ft_strdup(""));
	i = 0;
	while (token[i] && token[i] != '$')
		++i;
	refresh_args_val(&exp, ft_substr(token, 0, i), &i, 0);
	while (token[i])
	{
		j = 1;
		while (token[i + j] && is_var_name_char(token[i + j]))
			++j;
		if (token[i + j] == '?')
			refresh_args_val(&exp, ft_itoa(shell->last_exit_code), &i, j);
		else
		{
			exp.tk = ft_substr(token, i + 1, j - 1);
			if (!exp.tk)
				return (free(exp.res), ft_strdup(""));
			env_node = search_node(exp.tk, shell->env);
			if (!env_node || !env_node->value)
			{
				if (token[i])
					refresh_args_val(&exp, ft_substr(token, i, ft_strlen(token) - i), &i, 0);
				return (free(exp.tk), exp.res);
			}
			refresh_args_val(&exp, ft_strdup(env_node->value), &i, j);
			free(exp.tk);
		}
	}
	return (exp.res);
}

char	*expand_nested_quote(char *token, int is_here_doc)
{
	int i;
	t_expand exp;
	char quote;

	i = 0;
	quote = 0;
	exp.tk = ft_strdup(token);
	exp.res = ft_strdup("");
	if (!exp.tk || !exp.res)
		return (NULL);
	while (exp.tk[i])
	{
		if (!quote && ft_inset(exp.tk[i], "\'\""))
		{
			quote = exp.tk[i];
			if (is_here_doc)
				add_val(&exp, &i);
			else
				++i;
		}
		else if (quote && exp.tk[i] == quote)
		{
			quote = 0;
			if (is_here_doc)
				add_val(&exp, &i);
			else
				++i;
		}
		else
			add_val(&exp, &i);
	}
	return (free(exp.tk), exp.res);
}
