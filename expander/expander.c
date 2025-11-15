/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:43:30 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/15 19:38:12 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

static void	dollar_handler(char *token, int *i, t_shell *shell, t_expand *exp)
{
	int		j;
	char	*tmp;

	j = 1;
	while (token[*i + j] && is_var_name_char(token[*i + j]))
		++j;
	if (token[*i + j] == '?')
		refresh_args_val(exp, ft_itoa(g_status), i, 2);
	else if (j == 1)
		refresh_args_val(exp, ft_strdup("$"), i, 1);
	else
	{
		exp->tk = ft_substr(token, *i + 1, j - 1);
		tmp = get_value_from_env(shell->env, exp->tk);
		if (!tmp)
			tmp = ft_strdup("");
		else
			tmp = ft_strdup(tmp);
		refresh_args_val(exp, tmp, i, j);
		free(exp->tk);
	}
}

char	*expand_dollar_token(char *token, t_shell *shell, bool expand)
{
	t_expand	exp;
	int			i;
	int			j;

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
		while (token[j] && token[j] != '$')
			++j;
		refresh_args_val(&exp, ft_substr(token, i, j - i), &i, j - i);
		if (!token[i])
			break ;
		else
			dollar_handler(token, &i, shell, &exp);
	}
	return (exp.res);
}

char	*expand_nested_quote(char *token)
{
	int			i;
	char		quote;
	t_expand	exp;

	i = 0;
	quote = 0;
	exp.tk = token;
	exp.res = ft_strdup("");
	if (!token || !exp.res)
		return (NULL);
	while (token[i])
	{
		if (!quote && ft_inset(token[i], "\'\""))
		{
			quote = token[i++];
			while (token[i] && token[i] != quote)
				add_val(&exp, &i);
			if (token[i] == quote)
				++i;
			quote = 0;
		}
		else
			add_val(&exp, &i);
	}
	return (exp.res);
}
