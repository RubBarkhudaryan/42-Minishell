/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:43:30 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/11 22:12:16 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

char	*expand_dollar_token(char *token, t_shell *shell, bool expand)
{
	t_expand	exp;
	int			i;
	int			j;
	char		quote;

	if (!token || !shell || !shell->env)
		return (ft_strdup(""));
	if (!expand)
		return (ft_strdup(token));
	exp.res = ft_strdup("");
	if (!exp.res)
		return (NULL);
	i = 0;
	while (token[i])
	{
		j = i;
		while (token[j] && !ft_inset(token[j], "$\'\""))
			++j;
		refresh_args_val(&exp, ft_substr(token, i, j - i), &i, j - i);
		if (!token[i])
			break ;
		if (ft_inset(token[j], "\'\""))
		{
			i = j;
			quote = token[j++];
			while (token[j] && token[j] != quote)
				++j;
			refresh_args_val(&exp, ft_substr(token, i, j - i + 1), &i, j - i
				+ 1);
		}
		else
		{
			j = 1;
			while (token[i + j] && is_var_name_char(token[i + j]))
				++j;
			exp.tk = ft_substr(token, i + 1, j - 1);
			char *tmp = get_value_from_env(shell->env, exp.tk);
			if(!tmp)
				tmp = ft_strdup("");
			else
				tmp = ft_strdup(tmp);
			printf("temp: %s\n", tmp);
			refresh_args_val(&exp, tmp, &i, j);
			free(exp.tk);
		}
	}
	return (exp.res);
}

char	*expand_nested_quote(char *token, int is_here_doc)
{
	int			i;
	t_expand	exp;
	char		quote;

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
