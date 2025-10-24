/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/09/28 17:47:45 by apatvaka          #+#    #+#             */
/*   Updated: 2025/09/28 17:47:45 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer.h"


t_redir_cmd	*init_redir_cmd(void)
{
	t_redir_cmd *cmd;

	cmd = (t_redir_cmd *)malloc(sizeof(t_redir_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = NULL;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	add_redir(t_redir_cmd *cmd, int type, char *filename)
{
	t_redir *redir;
	t_redir *temp;

	redir = (t_redir *)malloc(sizeof(t_redir));
	if (!redir)
		return ;
	redir->is_expanded = 1;
	redir->type = type;
	redir->filename = ft_strdup(filename);
	redir->next = NULL;
	if (!cmd->redirs)
		cmd->redirs = redir;
	else
	{
		temp = cmd->redirs;
		while (temp->next)
			temp = temp->next;
		temp->next = redir;
	}
}

int	arg_count(char **argv)
{
	int i;

	if (!argv || !(*argv))
		return (0);
	i = 0;
	while (argv[i])
		++i;
	return (i);
}

void	add_arg(t_redir_cmd *cmd, char *arg)
{
	char **temp;
	int count;
	int i;

	i = 0;
	count = arg_count(cmd->argv);
	temp = (char **)malloc(sizeof(char *) * (count + 2));
	if (!temp)
		return ;
	while (i < count)
	{
		temp[i] = cmd->argv[i];
		++i;
	}
	temp[count] = ft_strdup(arg);
	// if(temp[count])
	// return ;
	temp[count + 1] = NULL;
	if (cmd->argv)
		free(cmd->argv);
	cmd->argv = temp;
}

void	free_redir_list(t_redir *redir, int flag_unlink_heredoc)
{
	t_redir *next;

	if (!redir)
		return ;
	while (redir)
	{
		next = redir->next;
		if (redir->type == TK_HEREDOC && flag_unlink_heredoc)
			unlink(redir->filename);
		free(redir->filename);
		free(redir);
		redir = next;
	}
}

void	free_redir_cmd(t_redir_cmd *cmd, int flag_unlink_heredoc)
{
	int i;
	t_redir_cmd *temp_cmd;
	t_redir_cmd *temp_next_cmd;

	temp_cmd = cmd;
	while (temp_cmd)
	{
		free_redir_list(temp_cmd->redirs, flag_unlink_heredoc);
		if (temp_cmd->argv)
		{
			i = -1;
			while (temp_cmd->argv && temp_cmd->argv[++i])
				free(temp_cmd->argv[i]);
			free(temp_cmd->argv);
		}
		temp_next_cmd = temp_cmd->next;
		free(temp_cmd);
		temp_cmd = temp_next_cmd;
	}
}
