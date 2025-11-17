/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 19:26:57 by rbarkhud          #+#    #+#             */
/*   Updated: 2025/11/17 02:15:01 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static char	*expand_splitted_arr(char **arr, t_shell *shell)
{
	int			j;
	int			expand;
	t_expand	exp;
	char		*res;

	j = -1;
	res = ft_strdup("");
	while (arr[++j])
	{
		expand = 1;
		if (arr[j][0] == '\'')
			expand = 0;
		exp.tk = expand_nested_quote(arr[j]);
		exp.res = expand_dollar_token(exp.tk, shell, expand);
		change_val(&arr[j], &exp.res);
		free(exp.tk);
		exp.tk = ft_strjoin(res, arr[j]);
		change_val(&res, &exp.tk);
	}
	return (res);
}

void	expand_command_redirections(t_cmd *cmd, t_shell *shell)
{
	char		**arr;
	t_redir		*redirs;

	if (cmd->redirs_cmd)
	{
		redirs = cmd->redirs_cmd;
		while (redirs)
		{
			if (redirs->type != TK_HEREDOC)
			{
				arr = split_by_quotes(redirs->filename);
				free(redirs->filename);
				redirs->filename = expand_splitted_arr(arr, shell);
				free_split(arr);
			}
			redirs = redirs->next;
		}
	}
}

void	expand_command_variables(t_ast *ast, t_shell *shell)
{
	int		i;
	char	**arr;

	i = -1;
	expand_command_redirections(ast->cmd, shell);
	while (ast->cmd->args && ast->cmd->args[++i])
	{
		arr = split_by_quotes(ast->cmd->args[i]);
		free(ast->cmd->args[i]);
		ast->cmd->args[i] = expand_splitted_arr(arr, shell);
		free_split(arr);
	}
	if (!ast->cmd->args)
		refresh_val(&ast->cmd->cmd_name, "");
	else
		refresh_val(&ast->cmd->cmd_name, ast->cmd->args[0]);
}
