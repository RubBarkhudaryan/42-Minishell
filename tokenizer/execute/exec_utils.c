/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 19:23:36 by apatvaka          #+#    #+#             */
/*   Updated: 2025/09/20 17:08:27 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

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
			return (free(exec_cmd), NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (free(exec_cmd), full_path);
		free(full_path);
	}
	return (free(exec_cmd), NULL);
}

static void	check_access(t_ast *ast, char **env_str, t_shell *shell)
{
	struct stat	statbuf;

	if (access(ast->cmd->cmd_name, F_OK) == -1)
	{
		print_msg(ast->cmd->cmd_name);
		free_split(env_str);
		free_shell(shell);
		exit(127);
	}
	if (access(ast->cmd->cmd_name, X_OK) == -1)
	{
		print_msg(ast->cmd->cmd_name);
		free_split(env_str);
		free_shell(shell);
		exit(126);
	}
	if (stat(ast->cmd->cmd_name, &statbuf) == 0 && S_ISDIR(statbuf.st_mode))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ast->cmd->cmd_name, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free_split(env_str);
		free_shell(shell);
		exit(126);
	}
}

static char	*handle_absolute_path(t_ast *ast, char **env_str, t_shell *shell)
{
	char	*result;

	check_access(ast, env_str, shell);
	result = ft_strdup(ast->cmd->cmd_name);
	if (!result)
	{
		perror("minishell");
		free_split(env_str);
		free_shell(shell);
		exit(1);
	}
	return (result);
}

static char	*handle_relative_path(t_ast *ast, char **env_str, t_shell *shell)
{
	char	**split_path;
	char	*result;
	char	*path;

	path = get_value_from_env(shell->env, "PATH");
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ast->cmd->cmd_name, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free_split(env_str);
		free_shell(shell);
		exit(127);
	}
	split_path = ft_split(path, ':');
	if (!split_path)
	{
		perror("minishell");
		free_shell(shell);
		exit(1);
	}
	result = search_path_dirs(ast->cmd->cmd_name, split_path);
	free_split(split_path);
	return (result);
}

char	*find_executable_path(t_ast *ast, char **env_str, t_shell *shell)
{
	if (ft_strchr(ast->cmd->cmd_name, '/'))
		return (handle_absolute_path(ast, env_str, shell));
	else
		return (handle_relative_path(ast, env_str, shell));
}
