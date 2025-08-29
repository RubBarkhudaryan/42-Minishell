/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/29 17:30:39 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/08/29 17:30:39 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	check_nested_quote(char curr_tk, char next_tk, int type)
{
	return ((curr_tk == '\\' && next_tk == '\"' && type == TK_DOUBLE_QUOTE)
		|| (curr_tk == '\\' && next_tk == '\'' && type == TK_SINGLE_QUOTE));
}

static void	refresh_args_val(t_expand *exp, char *join, int *ind, int inc_by)
{
	exp->piece = join_args(exp->res, join);
	change_val(&exp->res, &exp->piece);
	*ind = *ind + inc_by;
}

static void	handle_dollar(t_expand *exp, int *i, t_env *env)
{
	char	*dollar_tk;
	int		k;

	k = *i + 1;
	while (ft_isalpha(exp->tk[k]))
		++k;
	exp->piece = ft_substr(exp->tk, *i, k - *i);
	dollar_tk = expand_dollar_token(exp->piece, env);
	free(exp->piece);
	refresh_args_val(exp, dollar_tk, i, k - *i);
	free(dollar_tk);
}

char	*expand_dollar_token(char *token, t_env *env)
{
	t_env		*env_node;
	t_expand	exp;
	int			i;
	int			j;

	exp.res = ft_strdup("");
	if (!token || !(*token) || !env || !exp.res)
		return (free(exp.res), ft_strdup(""));
	i = 0;
	while (token[i])
	{
		j = 1;
		while (token[i + j] && ft_isalpha(token[i + j]))
			++j;
		exp.tk = ft_substr(token, i + 1, j - 1);
		if (!exp.tk)
			return (free(exp.res), ft_strdup(""));
		env_node = search_node(exp.tk, env);
		if (!env_node || !env_node->value)
			return (free(exp.tk), exp.res);
		refresh_args_val(&exp, env_node->value, &i, j);
		free(exp.tk);
	}
	return (exp.res);
}

char	*expand_nested_quote(char *token, int type, t_env *env)
{
	t_expand	exp;
	int			i;

	i = 0;
	exp.tk = ft_substr(token, 1, ft_strlen(token) - 2);
	exp.res = ft_strdup("");
	if (!exp.tk || !exp.res)
		return (NULL);
	while (exp.tk[i])
	{
		if (check_nested_quote(exp.tk[i], exp.tk[i + 1], type))
			refresh_args_val(&exp, (char [2]){exp.tk[i + 1], '\0'}, &i, 2);
		else if (exp.tk[i] == '$' && ft_isalpha(exp.tk[i + 1])
			&& type != TK_SINGLE_QUOTE)
			handle_dollar(&exp, &i, env);
		else
			refresh_args_val(&exp, (char [2]){exp.tk[i], '\0'}, &i, 1);
	}
	return (free(exp.tk), exp.res);
}
