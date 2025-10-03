/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:58:49 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/02 20:14:21 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ast.h"

void	free_cmd(t_cmd *cmd, int flag_unlink_heredoc)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->cmd_name)
		free(cmd->cmd_name);
	if (cmd->args)
	{
		i = -1;
		while (cmd->args[++i])
			free(cmd->args[i]);
		free(cmd->args);
	}
	if (cmd->redirs_cmd)
		free_redir_cmd(cmd->redirs_cmd, flag_unlink_heredoc);
	free(cmd);
}

static int	is_valid_token_type(t_token_type type)
{
	return (type == TK_WORD || type == TK_REDIR_INPUT || type == TK_REDIR_OUTPUT
		|| type == TK_APPEND || type == TK_HEREDOC);
}

static int	count_args(t_token *current)
{
	int	count;

	count = 0;
	while (current && is_valid_token_type(current->token_type))
	{
		count++;
		current = current->next;
	}
	return (count);
}

static int	fill_args(t_cmd *cmd, t_token **token_list, int arg_count)
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

int	is_redirection_type(t_token *token)
{
	while (token)
	{
		if (token->token_type == TK_REDIR_INPUT
			|| token->token_type == TK_REDIR_OUTPUT
			|| token->token_type == TK_APPEND
			|| token->token_type == TK_HEREDOC)
			return (1);
		token = token->next;
	}
	return (0);
}

char	**ft_splitdup(char **args)
{
	int		i;
	char	**ret;
	int		count;

	i = -1;
	count = args_len(args) + 1;
	ret = malloc(sizeof(char *) * count);
	if (!ret)
		return (NULL);
	while (args[++i])
	{
		printf("str = %s\n\n", args[i]);
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
		tmp = here_doc(cmd, tmp_red->filename, shell);
		if (!tmp)
			return (ft_putstr_fd("malloc failure", 2), NULL);
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
	cmd->args = cmd->redirs_cmd->argv;
	cmd->in_pipeline = -1;
	cmd->out_pipeline = -1;
	return (cmd);
}

t_cmd	*parse_redirs_ast(t_cmd *cmd, t_token **token_list, t_shell *shell)
{
	cmd->redirs_cmd = parse_redirs(token_list);
	print_redir_cmd(cmd->redirs_cmd);
	if (!cmd->redirs_cmd)
		return (free_redir_cmd(cmd->redirs_cmd, 0), free(cmd), NULL);
	if (cmd->redirs_cmd->redirs->type == TK_HEREDOC)
		return (handle_heredoc_redir(cmd, shell));
	else
		return (handle_other_redirs(cmd));
}

t_cmd	*give_token_for_cmd(t_token **token_list, t_shell *shell)
{
	t_cmd	*cmd;
	int		arg_count;

	if (!token_list || !*token_list)
		return (NULL);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	if (is_redirection_type((*token_list)))
		return (parse_redirs_ast(cmd, token_list, shell));
	cmd->redirs_cmd = NULL;
	arg_count = count_args(*token_list);
	cmd->cmd_name = ft_strdup((*token_list)->token);
	if (!cmd->cmd_name)
		return (free(cmd), NULL);
	cmd->in_pipeline = -1;
	cmd->out_pipeline = -1;
	if (!fill_args(cmd, token_list, arg_count))
		return (NULL);
	return (cmd);
}
