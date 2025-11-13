/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 22:43:30 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/13 18:00:05 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./expander.h"

char	*expand_dollar_token(char *token, t_shell *shell, bool expand)
{
	t_expand	exp;
	int			i;
	int			j;
	char		*tmp;

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
		while (token[j] && !ft_inset(token[j], "$"))
			++j;
		refresh_args_val(&exp, ft_substr(token, i, j - i), &i, j - i);
		if (!token[i])
			break ;
		else
		{
			j = 1;
			while (token[i + j] && is_var_name_char(token[i + j]))
				++j;
			if (token[i + j] == '?')
				refresh_args_val(&exp, ft_itoa(g_status), &i, j);
			exp.tk = ft_substr(token, i + 1, j - 1);
			tmp = get_value_from_env(shell->env, exp.tk);
			if (!tmp)
				tmp = ft_strdup("");
			else
				tmp = ft_strdup(tmp);
			refresh_args_val(&exp, tmp, &i, j);
			free(exp.tk);
		}
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
		if (!quote && token[i] != '\\' && ft_inset(token[i], "\'\""))
		{
			quote = token[i++];
			while (token[i])
			{
				if (token[i] != '\\' && token[i + 1] == quote)
					break ;
				add_val(&exp, &i);
			}
			if (token[i] == quote)
				++i;
			quote = 0;
		}
		else
			add_val(&exp, &i);
	}
	return (exp.res);
}

void	expand_command_redirections(t_cmd *cmd, t_shell *shell)
{
	int			i;
	int			expand;
	char		**arr;
	t_redir		*redirs;
	t_expand	exp;

	if (cmd->redirs_cmd)
	{
		redirs = cmd->redirs_cmd->redirs;
		while (redirs)
		{
			if (redirs->type != TK_HEREDOC)
			{
				i = -1;
				arr = split_by_quotes(redirs->filename);
				refresh_val(&redirs->filename, "");
				while (arr[++i])
				{
					expand = 1;
					if (arr[i][0] == '\'')
						expand = 0;
					exp.tk = expand_nested_quote(arr[i]);
					exp.res = expand_dollar_token(exp.tk, shell, expand);
					change_val(&arr[i], &exp.res);
					free(exp.tk);
					exp.tk = ft_strjoin(redirs->filename, arr[i]);
					change_val(&redirs->filename, &exp.tk);
				}
				free_split(arr);
			}
			redirs = redirs->next;
		}
	}
}

void	expand_command_variables(t_ast *ast, t_shell *shell)
{
	int			i;
	int			j;
	int			expand;
	char		**arr;
	t_expand	exp;

	i = -1;
	expand_command_redirections(ast->cmd, shell);
	while (ast->cmd->args && ast->cmd->args[++i])
	{
		j = -1;
		arr = split_by_quotes(ast->cmd->args[i]);
		refresh_val(&ast->cmd->args[i], "");
		while (arr[++j])
		{
			expand = 1;
			if (arr[j][0] == '\'')
				expand = 0;
			exp.tk = expand_nested_quote(arr[j]);
			exp.res = expand_dollar_token(exp.tk, shell, expand);
			change_val(&arr[j], &exp.res);
			free(exp.tk);
			exp.tk = ft_strjoin(ast->cmd->args[i], arr[j]);
			change_val(&ast->cmd->args[i], &exp.tk);
		}
		free_split(arr);
	}
	if (!ast->cmd->args)
		refresh_val(&ast->cmd->cmd_name, "");
	else
		refresh_val(&ast->cmd->cmd_name, ast->cmd->args[0]);
}
