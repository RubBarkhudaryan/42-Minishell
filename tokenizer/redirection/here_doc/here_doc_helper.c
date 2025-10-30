/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:26:22 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/30 20:21:03 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

void	print_heredoc_warning(int line, char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

static void	handle_heredoc_exit(t_cmd *cmd, t_shell *shell, char *filename,
		char *delimiter)
{
	close(cmd->redirs_cmd->redirs->heredoc_fd);
	free(delimiter);
	free(filename);
	free_cmd(cmd, 0);
	free_token_list(shell->token_list);
	free_env_list(shell->env);
	free(shell);
	exit(0);
}

static int	open_heredoc_file(char *filename, t_shell *shell)
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

int	process_heredoc_line(t_cmd *cmd, char *delimiter, char *filename,
		t_shell *shell)
{
	int		line_num;
	char	*line;
	char	*expanded;

	line_num = 1;
	line = readline("> ");
	if (!line)
		return (print_heredoc_warning(line_num, delimiter), free(line),
			handle_heredoc_exit(cmd, shell, filename, delimiter), 0);
	if (ft_strcmp(line, delimiter) == 0)
		return (free(line), handle_heredoc_exit(cmd, shell, filename,
				delimiter), 0);
	if (cmd->redirs_cmd->redirs->is_expanded)
	{
		expanded = expand_dollar_token(line, shell);
		free(line);
		line = expanded;
	}
	ft_putstr_fd(line, cmd->redirs_cmd->redirs->heredoc_fd);
	write(cmd->redirs_cmd->redirs->heredoc_fd, "\n", 1);
	free(line);
	line_num++;
	return (1);
}

void	run_heredoc_child(t_cmd *cmd, char *delimiter, char *filename,
		t_shell *shell)
{
	cmd->redirs_cmd->redirs->heredoc_fd = open_heredoc_file(filename, shell);
	while (1)
	{
		if (!process_heredoc_line(cmd, delimiter, filename, shell))
			break ;
	}
}
