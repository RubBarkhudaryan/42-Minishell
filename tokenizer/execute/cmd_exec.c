/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:19:14 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/30 00:28:39 by apatvaka         ###   ########.fr       */
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
		return (ft_strdup(cmd->cmd_name));
	split_path = ft_split(path, ':');
	if (!split_path)
		return (NULL);
	result = search_path_dirs(cmd->cmd_name, split_path);
	return (result);
}

int	apply_redirections(t_cmd *cmd, int extra_fd)
{
	// printf("\n\nalllo  in= %d\n", cmd->in_pipeline);
	// printf("alllo out= %d ========= %s\n\n", cmd->out_pipeline,
	// cmd->cmd_name);
	if (cmd->in_pipeline != -1)
	{
		if (dup2(cmd->in_pipeline, STDIN_FILENO) < 0)
			perror("dup:1 ");
		XCLOSE(cmd->in_pipeline);
	}
	if (cmd->out_pipeline != -1)
	{
		if (dup2(cmd->out_pipeline, STDOUT_FILENO) < 0)
			perror("dup: ");
		XCLOSE(cmd->out_pipeline);
	}
	if (extra_fd != -1)
		XCLOSE(extra_fd);
	return (0);
}

int	launch_process(t_cmd *cmd, char **env_str, int extra_fd, bool wait)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		apply_redirections(cmd, extra_fd);
		if (execve(cmd->cmd_name, cmd->args, env_str) == -1)
		{
			perror("execve");
			exit(1);
		}
	}
	if (!wait)
		return (0);
	return (waitpid(pid, &status, 0), get_exit_code(status));
}
