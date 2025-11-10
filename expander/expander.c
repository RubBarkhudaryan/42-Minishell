/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:43:30 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/10 21:19:55 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

char	*expand_dollar_token(char *token, t_shell *shell, bool skip_expand)
{
	t_env		*env_node;
	t_expand	exp;
	int			i;
	int			j;

	exp.res = ft_strdup("");
	if (!token || !(*token) || !shell->env || !exp.res)
		return (free(exp.res), ft_strdup(""));
	if ((token[0] == '\'' && token[1]) || skip_expand)
		return (free(exp.res), ft_strdup(token));
	i = 0;
	while (token[i])
	{
		j = i;
		while (token[j] && token[j] != '$')
			++j;
		refresh_args_val(&exp, ft_substr(token, i, j - i), &i, j - i);
		if (!token[i])
			break ;
		j = 1;
		while (token[i + j] && is_var_name_char(token[i + j]))
			++j;
		if (token[i + j] == '?')
			refresh_args_val(&exp, ft_itoa(shell->last_exit_code), &i, 2);
		else
		{
			exp.tk = ft_substr(token, i + 1, j - 1);
			if (!exp.tk)
				return (free(exp.res), ft_strdup(""));
			env_node = search_node(exp.tk, shell->env);
			if (!env_node || !env_node->value)
				refresh_args_val(&exp, ft_strdup(""), &i, j);
			else
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
