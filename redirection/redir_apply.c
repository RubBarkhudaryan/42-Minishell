/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:25:59 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/09 13:45:35 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execute/execute.h"

static int	token_len(t_token *tokens)
{
	int	len;

	len = 0;
	while (tokens)
	{
		len++;
		tokens = tokens->next;
	}
	return (len);
}

char	**tokens_to_args(t_token *tokens)
{
	t_token	*current;
	int		count;
	char	**args;
	int		i;

	count = token_len(tokens);
	args = malloc(sizeof(char *) * (count + 1));
	if (!count || !args)
		return (NULL);
	i = -1;
	current = tokens;
	args[count] = NULL;
	while (current)
	{
		args[++i] = ft_strdup(current->token);
		if (!args[i])
		{
			while (--i >= 0)
				free(args[i]);
			return (free(args), NULL);
		}
		current = current->next;
	}
	return (args);
}

int	open_fd(t_redir *redir, int redir_fd, int flags, mode_t mode)
{
	int	fd;

	fd = open(redir->filename, flags, mode);
	if (fd == -1)
		return (-1);
	if (redir->type == TK_HEREDOC)
		unlink(redir->filename);
	dup2(fd, redir_fd);
	close(fd);
	return (fd);
}

int	open_redirect_file(t_redir *redir, t_shell *shell)
{
	int	fd;

	fd = 0;
	(void)shell;
	if (redir->type == TK_REDIR_INPUT)
		fd = (open_fd(redir, STDIN_FILENO, O_RDONLY, 0));
	else if (redir->type == TK_REDIR_OUTPUT)
		fd = (open_fd(redir, STDOUT_FILENO, O_WRONLY | O_CREAT | O_TRUNC,
					0644));
	else if (redir->type == TK_APPEND)
		fd = (open_fd(redir, STDOUT_FILENO, O_WRONLY | O_CREAT | O_APPEND,
					0644));
	else if (redir->type == TK_HEREDOC)
		fd = (open_fd(redir, STDIN_FILENO, O_RDONLY, 0));
	if (fd == -1 && redir->type != TK_HEREDOC)
		print_msg(redir->filename);
	return (fd);
}

int	apply_redirections(t_shell *shell, t_cmd *cmd, int extra_fd)
{
	t_redir	*tmp;

	if (cmd->in_pipeline != -1)
	{
		dup2(cmd->in_pipeline, STDIN_FILENO);
		close(cmd->in_pipeline);
	}
	if (cmd->out_pipeline != -1)
	{
		dup2(cmd->out_pipeline, STDOUT_FILENO);
		close(cmd->out_pipeline);
	}
	if (extra_fd != -1)
		close(extra_fd);
	if (cmd->redirs_cmd)
	{
		tmp = cmd->redirs_cmd->redirs;
		while (tmp)
		{
			if (open_redirect_file(tmp, shell) == -1)
				return (EXIT_FAILURE);
			tmp = tmp->next;
		}
	}
	return (0);
}
