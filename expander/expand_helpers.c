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

int	is_var_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	check_nested_quote(char curr_tk, char next_tk)
{
	return ((curr_tk == '\\' && next_tk == '\"')
		|| (curr_tk == '\\' && next_tk == '\''));
}

void	refresh_args_val(t_expand *exp, char *join, int *ind, int inc_by)
{
	exp->piece = join_args(exp->res, join);
	change_val(&exp->res, &exp->piece);
	*ind = *ind + inc_by;
}

void	handle_dollar(t_expand *exp, int *i, t_shell *shell)
{
	char	*dollar_tk;
	int		k;

	k = *i + 1;
	if (ft_isdigit(exp->tk[k]))
		return ;
	while (exp->tk[k] && is_var_name_char(exp->tk[k]))
		++k;
	exp->piece = ft_substr(exp->tk, *i, k - *i);
	dollar_tk = expand_dollar_token(exp->piece, shell);
	free(exp->piece);
	refresh_args_val(exp, dollar_tk, i, k - *i);
	free(dollar_tk);
}

void	add_val(t_expand *exp, int *i)
{
	if (check_nested_quote(exp->tk[*i], exp->tk[*i + 1]))
		refresh_args_val(exp, (char [2]){exp->tk[*i + 1], '\0'}, i, 2);
	// else if (exp->tk[*i] == '$' && is_var_name_char(exp->tk[*i + 1])
	// 	&& quote != '\'' && !exp->is_here_doc)
	// 	handle_dollar(exp, i, env);
	else
		refresh_args_val(exp, (char [2]){exp->tk[*i], '\0'}, i, 1);
}
