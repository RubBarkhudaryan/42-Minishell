/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:19:14 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/17 18:21:51 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

static int	token_len(t_token *tokens)
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

static char	**tokens_to_args(t_token *tokens)
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

static char	*search_path_dirs(char *arg, char **split_path)
{
	int		i;
	char	*exec_cmd;
	char	*full_path;

	exec_cmd = ft_strjoin("/", arg);
	if (!exec_cmd)
		return (free_split(split_path), NULL);
	i = -1;
	while (split_path[++i])
	{
		full_path = ft_strjoin(split_path[i], exec_cmd);
		if (!full_path)
			return (free(exec_cmd), free_split(split_path), NULL);
		if (access(full_path, X_OK) == 0)
			return (free(exec_cmd), free_split(split_path), full_path);
		free(full_path);
	}
	return (free(exec_cmd), free_split(split_path), NULL);
}

static char	*find_executable_path(t_token *cmd, char *path)
{
	char	*arg;
	char	**split_path;
	char	*result;

	if (!cmd)
		return (NULL);
	arg = ft_strdup(cmd->token);
	if (!arg)
		return (NULL);
	if (access(arg, X_OK) == 0)
		return (arg);
	split_path = ft_split(path, ':');
	if (!split_path)
		return (free(arg), NULL);
	result = search_path_dirs(arg, split_path);
	return (free(arg), result);
}

int	launch_process(char **args, char *exec_path, char **env_str)
{
	pid_t	pid;
	int		status;

	if (!args)
		return (free(exec_path), free_split(env_str), 1);
	pid = fork();
	if (pid == 0)
	{
		if (execve(exec_path, args, env_str) == -1)
			return (1);
	}
	waitpid(pid, &status, 0);
	return (status);
}
