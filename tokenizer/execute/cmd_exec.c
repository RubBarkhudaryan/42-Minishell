/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:19:14 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/24 22:19:50 by apatvaka         ###   ########.fr       */
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

char	*find_executable_path(t_cmd *cmd, char *path)
{
	char	**split_path;
	char	*result;

	if (!cmd->cmd_name || !(*cmd->cmd_name))
		return (NULL);
	if (access(cmd->cmd_name, X_OK) == 0)
		return (cmd->cmd_name);
	split_path = ft_split(path, ':');
	if (!split_path)
		return (NULL);
	result = search_path_dirs(cmd->cmd_name, split_path);
	return (result);
}

int	launch_process(char **args, char *exec_path, char **env_str, bool wait)
{
	pid_t	pid;
	int		status;

	if (!args)
		return (1);
	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		if (execve(exec_path, args, env_str) == -1)
		{
			perror("execve");
			exit(1);
		}
	if (!wait)
		return (0);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
