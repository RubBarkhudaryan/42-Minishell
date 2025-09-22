/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 17:09:32 by apatvaka          #+#    #+#             */
/*   Updated: 2025/09/21 20:35:43 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tokenizer.h"

void	print_heredoc_warning(int line, char *delimiter)
{
	ft_putstr_fd("minishell: warning: here-document at line ", STDERR_FILENO);
	ft_putnbr_fd(line, STDERR_FILENO);
	ft_putstr_fd(" delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

void	run_heredoc_child(t_cmd *cmd, char *delimiter, char *filename,
		t_shell *shell, t_redir_cmd *redir_cmd)
{
	int		fd;
	int		line_num;
	char	*line;

	fd = open(filename, O_CREAT | O_EXCL | O_WRONLY, 0644);
	if (fd == -1)
	{
		free(filename);
		free_shell(shell);
		perror("minishell");
		exit(1);
	}
	(void)cmd;
	(void)redir_cmd;
	line_num = 1;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_heredoc_warning(line_num, delimiter);
			close(fd);
			free(filename);
			free_cmd(cmd);
			free_shell(shell);
			exit(0);
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			close(fd);
			free(filename);
			free_cmd(cmd);
			free_token_list(shell->token_list);
			free_shell(shell);
			exit(0);
		}
		ft_putstr_fd(line, fd);
		write(fd, "\n", 1);
		free(line);
		line_num++;
	}
}

int	run_here_doc(t_cmd *cmd, char *delimiter, char *filename, t_shell *shell,
		t_redir_cmd *redir_cmd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (free(filename), perror("minishell"), EXIT_FAILURE);
	if (pid == 0)
		run_heredoc_child(cmd, delimiter, filename, shell, redir_cmd);
	return (waitpid(pid, &status, 0), get_exit_code(status));
}

char	*open_check_filename(void)
{
	char	*filename;
	char	*tmp;
	int		index;

	index = 0;
	while (1)
	{
		tmp = ft_itoa(index++);
		if (!tmp)
		{
			perror("minishell");
			return (NULL);
		}
		filename = ft_strjoin("/tmp/.her_doc", tmp);
		if (!filename)
		{
			free(tmp);
			perror("minishell");
			return (NULL);
		}
		free(tmp);
		if (access(filename, F_OK) != 0)
			return (filename);
		free(filename);
	}
}

char	*here_doc(t_cmd *cmd, char *delimiter, t_shell *shell,
		t_redir_cmd *redir_cmd)
{
	char	*file_name;

	file_name = open_check_filename();
	if (!file_name)
		return (NULL);
	shell->last_exit_code = run_here_doc(cmd, delimiter, file_name, shell,
			redir_cmd);
	if (shell->last_exit_code == EXIT_FAILURE)
		return (free(file_name), NULL);
	// unlink(file_name);
	return (file_name);
}
