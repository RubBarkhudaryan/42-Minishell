/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbarkhud <rbarkhud@student.42yerevan.am    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:25 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/25 14:33:56 by rbarkhud         ###   ########.fr       */
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

	(void)extra_fd;
	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	if (pid == 0)
		if (execute_builtin(cmd->cmd_name, cmd->args, env))
			exit(1);
	if (!wait)
		return (0);
	waitpid(pid, &status, 0);
	return (get_exit_code(status));
}

int	execute_command(t_ast *ast, t_env *env, bool wait, int extra_fd)
{
	char	**env_str;
	char	*path;
	char	*exec_path;
	int		status;

	(void)extra_fd;
	if (is_builtin(ast->cmd->cmd_name) && ast->cmd->in_pipeline == -1
		&& ast->cmd->in_pipeline == -1)
		return (execute_builtin(ast->cmd->cmd_name, ast->cmd->args, env));
	else if (is_builtin(ast->cmd->cmd_name))
		return (exe_builtin_process(ast->cmd, env, wait, extra_fd));
	env_str = convert_envp_to_string(env);
	if (!env_str)
		return (free_ast(ast), 1);
	path = get_value_from_env(env, "PATH");
	if (!path)
		return (free_split(env_str), 1);
	exec_path = find_executable_path(ast->cmd, path);
	if (!exec_path)
		return (free_split(env_str), 1);
	status = launch_process(ast->cmd->args, exec_path, env_str, wait);
	return (free(exec_path), free_split(env_str), status);
}

// int	execute_pipe(t_ast *ast, t_env *env, bool wait)
// {
// 	int	pipefd[2];

// 	if (ast->left->type == NODE_PIPE)
// 		return (execute_pipe(ast->left, env, false));
// 	if (pipe(pipefd) == -1)
// 		return (perror("pipe"), 1);
// }

int	execute_ast(t_ast *ast, t_env *env, bool wait)
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
	// if (ast->type == NODE_PIPE)
	// 	return (execute_pipe(ast, env, wait, -1));
	// else
	if (ast->type == NODE_COMMAND)
		return (execute_command(ast, env, wait, -1));
	return (0);
}

int	execute_node(t_ast *ast, t_env *env)
{
	if (!ast)
		return (1);
	return (execute_ast(ast, env, true));
}
