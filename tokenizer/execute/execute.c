/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/12 14:40:25 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/16 00:14:40 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	token_len(t_token *tokens)
{
	int	len;

	len = 0;
	while (tokens)
	{
		len++;
		tokens = tokens->next;
	}
	return (len);
}

char	**tokens_to_args(t_token *tokens)
{
	t_token	*current;
	int		count;
	char	**args;
	int		i;

	count = token_len(tokens);
	args = malloc(sizeof(char *) * (count + 1));
	if (!count || !args)
		return (NULL);
	i = -1;
	current = tokens;
	args[count] = NULL;
	while (current)
	{
		args[++i] = ft_strdup(current->token);
		if (!args[i])
		{
			while (--i >= 0)
				free(args[i]);
			return (free(args), NULL);
		}
		current = current->next;
	}
	return (args);
}

char	*find_executable_path(t_token *cmd, char *path)
{
	char	**split_path;
	int		i;
	char	*exec_cmd;
	char	*full_path;

	if (access(cmd->token, X_OK) == 0)
		return (cmd->token);
	split_path = ft_split(path, ':');
	if (!split_path)
		return (NULL);
	i = -1;
	exec_cmd = ft_strjoin("/", cmd->token);
	if (exec_cmd == NULL)
		return (free_split(split_path), NULL);
	while (split_path[++i])
	{
		full_path = ft_strjoin(split_path[i], exec_cmd);
		if (!full_path)
			return (free(exec_cmd), free_split(split_path), NULL);
		if (access(full_path, X_OK) == 0)
			return (free(exec_cmd), free_split(split_path), full_path);
		free(full_path);
	}
	return (free(full_path), free(exec_cmd), free_split(split_path), NULL);
}

int	execute_command(t_ast *ast, t_env *env)
{
	char	**env_str;
	char	*path;
	char	*exec_path;
	char	**args;
	pid_t	pid;
	int		status;

	env_str = convert_envp_to_string(env);
	if (!env_str)
		return (1);
	path = get_value_from_env(env, "PATH");
	if (!path)
		return (1);
	exec_path = find_executable_path(ast->cmd, path);
	if (!exec_path)
		return (free_split(env_str), 1);
	args = tokens_to_args(ast->cmd);
	if (!args)
		return (free(exec_path), free_split(env_str), 1);
	pid = fork();
	if (pid == 0)
	{
		if (execve(exec_path, args, env_str) == -1)
		{
			perror("execve");
			free(exec_path);
			free_split(env_str);
			free_split(args);
			return (1);
		}
	}
	waitpid(pid, &status, 0);
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
	// else if (ast->type == NODE_PIPE)
	// 	return (execute_pipe(ast, env));
	// else
	if (ast->type == NODE_COMMAND)
		return (execute_command(ast, env));
	return (0);
}
