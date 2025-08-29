/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:25 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/30 00:32:02 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// int	prepare_command(t_ast *ast, t_env *env)
// {
// }

int	exe_builtin_process(t_cmd *cmd, t_env *env, bool wait, int extra_fd)
{
	pid_t	pid;
	int		status;

	apply_redirections(cmd, extra_fd);
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
		if (execute_builtin(cmd, env))
			exit(1);
	if (extra_fd != -1)
		XCLOSE(extra_fd);
	if (!wait)
		return (0);
	waitpid(pid, &status, 0);
	return (get_exit_code(status));
}

int	execute_command(t_ast *ast, t_env *env, bool wait, int extra_fd)
{
	char	**env_str;
	char	*path;
	char	*tmp;
	int		status;

	if (is_builtin(ast->cmd->cmd_name) && ast->cmd->in_pipeline == -1
		&& ast->cmd->in_pipeline == -1)
		return (execute_builtin(ast->cmd, env));
	else if (is_builtin(ast->cmd->cmd_name))
		return (exe_builtin_process(ast->cmd, env, wait, extra_fd));
	env_str = convert_envp_to_string(env);
	if (!env_str)
		return (free_ast(ast), 1);
	path = get_value_from_env(env, "PATH");
	if (!path)
		return (free_split(env_str), 1);
	tmp = find_executable_path(ast->cmd, path);
	free(ast->cmd->cmd_name);
	ast->cmd->cmd_name = tmp;
	if (!ast->cmd->cmd_name)
		return (free_split(env_str), 1);
	status = launch_process(ast->cmd, env_str, extra_fd, wait);
	return (free_split(env_str), status);
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
}

int	last_pipe_exec(t_ast *ast, t_env *env, int pipe_fd)
{
	int	exit_code;
	int	status;

	// (void)pipe_fd;
	exit_code = execute_ast(ast, env, true, -1);
	XCLOSE(pipe_fd);
	while (wait(&status) != -1)
		;
	return (exit_code);
}

// STDIN_FILENO 0
// STDOUT_FILENO 1
int	execute_pipe(t_ast *ast, t_env *env, bool last_pipe)
{
	int	pipe_fd[2];
	int	extra_fd;

	if (ast->left->type == NODE_PIPE)
		extra_fd = execute_pipe(ast->left, env, false);
	else
		extra_fd = -1;
	if (pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	setup_pipe_fds(ast->left, pipe_fd[1], STDOUT_FILENO);
	setup_pipe_fds(ast->right, pipe_fd[0], STDIN_FILENO);
	if (ast->left->type == NODE_PIPE)
		execute_ast(ast->left->right, env, false, pipe_fd[0]);
	else
		execute_ast(ast->left, env, false, pipe_fd[0]);
	XCLOSE(pipe_fd[1]);
	if (extra_fd != -1)
		XCLOSE(extra_fd);
	if (last_pipe == true)
		return (last_pipe_exec(ast->right, env, pipe_fd[0]));
	return (pipe_fd[0]);
}
//execute/cmd_exec.c:112
// execute/cmd_exec.c:103
//
// execute/execute.c:109
// execute/execute.c:111
int	execute_ast(t_ast *ast, t_env *env, bool wait, int extra_fd)
{
	if (!ast)
		return (1);
	// if (ast->type == NODE_AND)
	// 	return (execute_ast(ast->left, env) && execute_ast(ast->right, env));
	// 		// Change this to another function to start a new process.
	// else if (ast->type == NODE_OR)
	// 	return (execute_ast(ast->left, env) || execute_ast(ast->right, env));
	// 		// Change this to another function to start a new process.
	// else
	if (ast->type == NODE_PIPE)
		return (execute_pipe(ast, env, wait));
	else if (ast->type == NODE_COMMAND)
		return (execute_command(ast, env, wait, extra_fd));
	return (0);
}

int	execute_node(t_ast *ast, t_env *env)
{
	if (!ast)
		return (1);
	return (execute_ast(ast, env, true, -1));
}
