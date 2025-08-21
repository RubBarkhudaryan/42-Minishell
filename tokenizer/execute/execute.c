/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:25 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/19 15:24:47 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

// int	prepare_command(t_ast *ast, t_env *env)
// {
// }

int	execute_command(t_ast *ast, t_env *env)
{
	char	**env_str;
	char	*path;
	char	*exec_path;
	char	**args;
	int		status;

	args = tokens_to_args(ast->cmd);
	if (!args)
		return (1);
	if (is_builtin(ast->cmd->token))
		return (execute_builtin(ast->cmd->token, args, env));
	env_str = convert_envp_to_string(env);
	if (!env_str)
		return (free_split(args), 1);
	path = get_value_from_env(env, "PATH");
	if (!path)
		return (1);
	exec_path = find_executable_path(ast->cmd, path);
	if (!exec_path)
		return (free_split(args), free_split(env_str), 1);
	status = launch_process(args, exec_path, env_str);
	free(exec_path);
	free_split(env_str);
	free_split(args);
	return (status);
}

// int	execute_pipe(t_ast *ast, t_env *env)
// {
// 	int		pipefd[2];
// 	pid_t	pid1;
// 	pid_t	pid2;

// 	if (pipe(pipefd) == -1)
// 		return (perror("pipe"), 1);
// 	pid
// }

int	execute_ast(t_ast *ast, t_env *env)
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
	// 	return (execute_pipe(ast, env));
	// else
	if (ast->type == NODE_COMMAND)
		return (execute_command(ast, env));
	return (0);
}
