/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:26:22 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/06 20:12:19 by apatvaka         ###   ########.fr       */
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
		expanded = expand_dollar_token(line, shell);
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
	cmd->redirs_cmd->redirs->heredoc_fd = open_heredoc_file(here_doc_data.filename,
			shell);
	here_doc_data.line_count = 1;
	while (1)
	{
		if (!process_heredoc_line(cmd, here_doc_data, shell))
			break ;
	}
}

// static void	handle_heredoc_exit(t_cmd *cmd, t_shell *shell,
// 		t_here_doc here_doc_data, t_ast *left)
// {
// 	t_token	*tmp;

// 	// t_token	*tmp1;
// 	// t_token	*tmp2;
// 	close(cmd->redirs_cmd->redirs->heredoc_fd);
// 	free(here_doc_data.delimiter);
// 	free(here_doc_data.filename);
// 	free_cmd(cmd, 0);
// 	free_ast(left, 0);
// 	if (shell->token_list_subshell)
// 	{
// 		tmp2 = shell->token_list_subshell;
// 		tmp = shell->token_list;
// 		while (tmp->next)
// 		{
// 			printf("AFTER HEREDOC CHILD = %s\n", tmp->token);
// 			tmp = tmp->next;
// 		}
// 		while (tmp2)
// 		{
// 			printf("SAVED SUBSHELL TOKENS = %s\n", tmp2->token);
// 			tmp2 = tmp2->next;
// 		}
// 		tmp->next = shell->token_list_subshell;
// 		shell->token_list_subshell = NULL;
// 	}
// 	tmp1 = shell->token_list;
// 	while (tmp1)
// 	{
// 		printf("aloooo == %s\n", tmp1->token);
// 		tmp1 = tmp1->next;
// 	}
// 	free_token_list(shell->token_list);
// 	free_env_list(shell->env);
// 	free(shell);
// 	exit(0);
// }
