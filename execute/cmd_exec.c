/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:19:14 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/30 18:29:10 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

void	print_msg(char *name)
{
	char	*msg;

	if (!name)
		perror("minishell");
	msg = ft_strjoin("minishell: ", name);
	if (!msg)
		perror("minishell");
	perror(msg);
	free(msg);
}

static int	execute_command(t_ast *ast, t_shell *shell, int extra_fd,
		char **env_str)
{
	if (apply_redirections(shell, ast->cmd, extra_fd) == 1)
	{
		free_split(env_str);
		free_shell(shell, 1);
		exit(EXIT_FAILURE);
	}
	if (ast->cmd->cmd_name)
		execve(ast->cmd->cmd_name, ast->cmd->args, env_str);
	else if (ast->cmd->redirs_cmd)
	{
		free_split(env_str);
		free_shell(shell, 0);
		exit(0);
	}
	perror("execve");
	free_split(env_str);
	free_shell(shell, 0);
	exit(126);
}

static int	handle_child_process(t_ast *ast, t_shell *shell, int extra_fd,
		char **env_str)
{
	char	*tmp;

	tmp = find_executable_path(ast, env_str, shell);
	if (!tmp && ast->cmd->redirs_cmd == NULL)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(ast->cmd->cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_split(env_str);
		free_shell(shell, 0);
		exit(127);
	}
	if (ast->cmd->cmd_name)
	{
		free(ast->cmd->cmd_name);
		ast->cmd->cmd_name = tmp;
	}
	return (execute_command(ast, shell, extra_fd, env_str));
}

int	launch_process(t_ast *ast, t_shell *shell, int extra_fd, bool wait)
{
	pid_t	pid;
	char	**env_str;
	int		status;

	env_str = convert_envp_to_string(shell->env);
	if (!env_str)
	{
		perror("minishell");
		free_split(env_str);
		return (free_shell(shell, 0), 1);
	}
	pid = fork();
	if (pid == -1)
		return (free_split(env_str), free_shell(shell, 1), perror("minishell"),
			1);
	if (pid == 0)
		handle_child_process(ast, shell, extra_fd, env_str);
	free_split(env_str);
	if (!wait)
		return (0);
	return (waitpid(pid, &status, 0), get_exit_code(status));
}
