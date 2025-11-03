/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 17:59:39 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/03 19:45:57 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

static char	**ft_splitdup(char **args)
{
	int		i;
	char	**ret;
	int		count;

	i = -1;
	count = args_len(args) + 1;
	ret = malloc(sizeof(char *) * count);
	if (!ret)
		return (NULL);
	while (args && args[++i])
	{
		ret[i] = ft_strdup(args[i]);
		if (!ret[i])
		{
			free_split(ret);
			return (NULL);
		}
	}
	ret[i] = NULL;
	return (ret);
}

static t_cmd	*handle_heredoc_redir(t_cmd *cmd, t_shell *shell)
{
	char	*tmp;
	t_redir	*tmp_red;

	if (cmd->redirs_cmd->argv)
	{
		cmd->cmd_name = ft_strdup(cmd->redirs_cmd->argv[0]);
		cmd->args = ft_splitdup(cmd->redirs_cmd->argv);
	}
	else
	{
		cmd->args = NULL;
		cmd->cmd_name = NULL;
	}
	tmp_red = cmd->redirs_cmd->redirs;
	while (tmp_red && tmp_red->type == TK_HEREDOC)
	{
		printf("heredoc [%s]\n\n", tmp_red->filename);
		tmp = here_doc(cmd, ft_strdup(tmp_red->filename), shell);
		if (!tmp)
			return (ft_putstr_fd("malloc failure\n", 2), NULL);
		free(tmp_red->filename);
		tmp_red->filename = tmp;
		tmp_red = tmp_red->next;
	}
	cmd->in_pipeline = -1;
	cmd->out_pipeline = -1;
	return (cmd);
}

static t_cmd	*handle_other_redirs(t_cmd *cmd)
{
	if (cmd->redirs_cmd->argv && cmd->redirs_cmd->argv[0])
		cmd->cmd_name = ft_strdup(cmd->redirs_cmd->argv[0]);
	else
		cmd->cmd_name = NULL;
	if (cmd->redirs_cmd->argv)
		cmd->args = ft_splitdup(cmd->redirs_cmd->argv);
	else
		cmd->args = NULL;
	cmd->in_pipeline = -1;
	cmd->out_pipeline = -1;
	return (cmd);
}

t_cmd	*parse_redirs_ast(t_cmd *cmd, t_token **token_list,
		t_shell *shell)
{
	while ((*token_list) && (*token_list)->token_type == TK_R_PARENTHESIS)
		(*token_list) = (*token_list)->next;
	cmd->redirs_cmd = parse_redirs(token_list);
	if (!cmd->redirs_cmd)
		return (free_redir_cmd(cmd->redirs_cmd, 0), free(cmd), NULL);
	if (cmd->redirs_cmd->redirs && cmd->redirs_cmd->redirs->type == TK_HEREDOC)
		return (handle_heredoc_redir(cmd,  shell));
	else
		return (handle_other_redirs(cmd));
}
int	is_valid_token_type(t_token_type type)
{
	return (type == TK_WORD || type == TK_REDIR_INPUT || type == TK_REDIR_OUTPUT
		|| type == TK_APPEND || type == TK_HEREDOC);
}

int	fill_args(t_cmd *cmd, t_token **token_list, int arg_count)
{
	int	i;

	cmd->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!cmd->args)
		return (0);
	i = 0;
	while (*token_list && is_valid_token_type((*token_list)->token_type))
	{
		cmd->args[i] = ft_strdup((*token_list)->token);
		if (!cmd->args[i])
			return (free_cmd(cmd, 0), 0);
		*token_list = (*token_list)->next;
		i++;
	}
	cmd->args[i] = NULL;
	return (1);
}
