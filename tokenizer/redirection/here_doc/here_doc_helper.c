/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:26:22 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/25 18:02:12 by rbarkhud         ###   ########.fr       */
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
		int fd)
{
	close(fd);
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

void	run_heredoc_child(t_cmd *cmd, char *delimiter, char *filename,
		t_shell *shell)
{
	int		fd;
	int		line_num;
	char	*line;
	char	*tmp;

	fd = open_heredoc_file(filename, shell);
	line_num = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_heredoc_warning(line_num, delimiter);
			free(line);
			handle_heredoc_exit(cmd, shell, filename, fd);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			handle_heredoc_exit(cmd, shell, filename, fd);
		}
		if (cmd->redirs_cmd->redirs->is_expanded)
		{
			tmp = expand_dollar_token(line, shell);
			free(line);
			line = tmp;
		}
		
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
		line_num++;
	}
}
