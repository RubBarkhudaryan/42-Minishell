/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:26:22 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/11 22:12:26 by rbarkhud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./here_doc.h"

void	print_heredoc_warning(int line, char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static void	handle_heredoc_exit(t_cmd *cmd, t_shell *shell,
		t_here_doc here_doc_data)
{
	close(cmd->redirs_cmd->redirs->heredoc_fd);
	free(here_doc_data.delimiter);
	free(here_doc_data.filename);
	free_token_list(shell->token_list);
	free_shell(shell, 0);
	exit(0);
}

static int	open_heredoc(char *filename, t_shell *shell)
{
	int	fd;

	fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0644);
	if (fd == -1)
	{
		free_shell(shell, 0);
		perror("minishell");
		exit(1);
	}
	return (fd);
}

int	process_heredoc_line(t_cmd *cmd, t_here_doc here_doc_data, t_shell *shell)
{
	char	*line;
	char	*expanded;

	line = readline("> ");
	if (!line)
		return (print_heredoc_warning(here_doc_data.line_count,
				here_doc_data.delimiter), free(line), handle_heredoc_exit(cmd,
				shell, here_doc_data), 0);
	if (ft_strcmp(line, here_doc_data.delimiter) == 0)
		return (free(line), handle_heredoc_exit(cmd, shell, here_doc_data), 0);
	if (cmd->redirs_cmd->redirs->is_expanded)
	{
		expanded = expand_dollar_token(line, shell, 1);
		free(line);
		line = expanded;
	}
	ft_putstr_fd(line, cmd->redirs_cmd->redirs->heredoc_fd);
	write(cmd->redirs_cmd->redirs->heredoc_fd, "\n", 1);
	free(line);
	(here_doc_data.line_count)++;
	return (1);
}

void	run_heredoc_child(t_cmd *cmd, t_here_doc here_doc_data, t_shell *shell)
{
	cmd->redirs_cmd->redirs->heredoc_fd = open_heredoc(here_doc_data.filename,
			shell);
	here_doc_data.line_count = 1;
	while (1)
	{
		if (!process_heredoc_line(cmd, here_doc_data, shell))
			break ;
	}
}
