/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:25:57 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/07 18:53:39 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	exe_builtin_process(t_cmd *cmd, t_shell *shell, bool wait, int extra_fd)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (perror("minishell"), EXIT_FAILURE);
	if (pid == 0)
	{
		apply_redirections(shell, cmd, extra_fd);
		if (execute_builtin(cmd, shell))
		{
			free_shell(shell, 0);
			exit(1);
		}
		free_shell(shell, 0);
		exit(0);
	}
	if (!wait)
		return (0);
	waitpid(pid, &status, 0);
	return (get_exit_code(status));
}

void	setup_pipe_fds(t_ast *ast, int pipefd, int type_fd)
{
	if (ast->type == NODE_COMMAND)
	{
		if (type_fd == STDOUT_FILENO)
			ast->cmd->out_pipeline = pipefd;
		else
			ast->cmd->in_pipeline = pipefd;
	}
	else if (ast->type == NODE_SUBSHELL)
	{
		if (type_fd == STDOUT_FILENO)
			ast->cmd->out_pipeline = pipefd;
		else
			ast->cmd->in_pipeline = pipefd;
		setup_pipe_fds(ast->left, pipefd, type_fd);
	}
	else if (ast->type == NODE_PIPE)
		setup_pipe_fds(ast->right, pipefd, type_fd);
}

int	last_pipe_exec(t_ast *ast, t_shell *shell, int pipe_fd)
{
	int	exit_code;
	int	status;

	exit_code = execute_ast(ast, shell, true, -1);
	close(pipe_fd);
	while (wait(&status) != -1)
		;
	return (exit_code);
}

int	execute_pipe(t_ast *ast, t_shell *shell, bool last_pipe)
{
	int	pipe_fd[2];
	int	extra_fd;

	if (ast->left->type == NODE_PIPE)
		extra_fd = execute_pipe(ast->left, shell, false);
	else
		extra_fd = -1;
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	setup_pipe_fds(ast->left, pipe_fd[1], STDOUT_FILENO);
	setup_pipe_fds(ast->right, pipe_fd[0], STDIN_FILENO);
	if (ast->left->type == NODE_PIPE)
		execute_ast(ast->left->right, shell, false, pipe_fd[0]);
	else
		execute_ast(ast->left, shell, false, pipe_fd[0]);
	close(pipe_fd[1]);
	if (extra_fd != -1)
		close(extra_fd);
	if (last_pipe == true)
		return (last_pipe_exec(ast->right, shell, pipe_fd[0]));
	return (pipe_fd[0]);
}
