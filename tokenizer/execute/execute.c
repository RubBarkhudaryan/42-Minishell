/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:25 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/17 18:37:22 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	execute_builtin(char *cmd, char **args, t_env *env)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(args, env));
	else if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(args));
	else if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(args, env));
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(args, &env));
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(args));
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(args, env));
	// else if (ft_strcmp(cmd, "exit") == 0)
	return (-1);
}

int	execute_command(t_ast *ast, t_env *env)
{
	char	**env_str;
	char	*path;
	char	*exec_path;
	char	**args;
	int		status;

	env_str = convert_envp_to_string(env);
	if (!env_str)
		return (1);
	args = tokens_to_args(ast->cmd);
	if (!args)
		return (free_split(env_str), 1);
	if (is_builtin(ast->cmd->token))
		return (execute_builtin(ast->cmd->token, args, env));
	path = get_value_from_env(env, "PATH");
	if (!path)
		return (1);
	exec_path = find_executable_path(ast->cmd, path);
	if (!exec_path)
		return (free_split(env_str), 1);
	status = launch_process(args, exec_path, env_str);
	free(exec_path);
	free_split(env_str);
	free_split(args);
	return (status);
}

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
	// return (execute_pipe(ast, env));
	// else
	if (ast->type == NODE_COMMAND)
		return (execute_command(ast, env));
	return (0);
}
