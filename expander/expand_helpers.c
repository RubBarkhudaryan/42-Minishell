/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_helpers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:49:15 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/09/12 22:49:15 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	check_nested_quote(char curr_tk, char next_tk)
{
	return ((curr_tk == '\\' && next_tk == '\"')
		|| (curr_tk == '\\' && next_tk == '\''));
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

void	add_val(t_expand *exp, t_env *env, int *i, char quote)
{
	if (check_nested_quote(exp->tk[*i], exp->tk[*i + 1]))
		refresh_args_val(exp, (char [2]){exp->tk[*i + 1], '\0'}, i, 2);
	else if (exp->tk[*i] == '$' && ft_isalpha(exp->tk[*i + 1]) && quote != '\''
		&& !exp->is_here_doc)
		handle_dollar(exp, i, env);
	else
		refresh_args_val(exp, (char [2]){exp->tk[*i], '\0'}, i, 1);
}

char	*expand_nested_quote(char *token, t_env *env, int is_here_doc)
{
	int			i;
	t_expand	exp;
	char		quote;

	i = 0;
	quote = 0;
	exp.tk = ft_strdup(token);
	exp.res = ft_strdup("");
	exp.is_here_doc = is_here_doc;
	if (!exp.tk || !exp.res)
		return (NULL);
	while (exp.tk[i])
	{
		if (!quote && ft_inset(exp.tk[i], "\'\""))
			quote = exp.tk[i++];
		else if (quote && exp.tk[i] == quote)
		{
			quote = 0;
			++i;
		}
		else
			add_val(&exp, env, &i, quote);
	}
	return (free(exp.tk), exp.res);
}
