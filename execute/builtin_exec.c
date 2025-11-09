/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:23:30 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/09 14:07:33 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

int	is_builtin(char *cmd)
{
	if (!cmd || !*cmd)
		return (0);
	return (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	execute_builtin_direct(t_ast *ast, t_shell *shell)
{
	int	status;

	status = 0;
	if (ft_strcmp(ast->cmd->cmd_name, "cd") == 0)
		status = ft_cd(ast->cmd->args, shell);
	else if (ft_strcmp(ast->cmd->cmd_name, "echo") == 0)
		status = ft_echo(ast->cmd->args);
	else if (ft_strcmp(ast->cmd->cmd_name, "env") == 0)
		status = ft_env(ast->cmd->args, shell);
	else if (ft_strcmp(ast->cmd->cmd_name, "export") == 0)
		status = ft_export(ast->cmd->args, shell);
	else if (ft_strcmp(ast->cmd->cmd_name, "pwd") == 0)
		status = ft_pwd(shell->env);
	else if (ft_strcmp(ast->cmd->cmd_name, "unset") == 0)
		status = ft_unset(ast->cmd->args, &(shell->env));
	else if (ft_strcmp(ast->cmd->cmd_name, "exit") == 0)
		status = ft_exit(ast->cmd->args, shell);
	return (status);
}

static int	setup_and_restore_fds(int extra_fd, int old_fds[2])
{
	if (extra_fd == -1)
	{
		old_fds[0] = dup(STDIN_FILENO);
		old_fds[1] = dup(STDOUT_FILENO);
		if (old_fds[0] == -1 || old_fds[1] == -1)
			return (0);
	}
	return (1);
}

static void	restore_fds(int extra_fd, int old_stdin, int old_stdout)
{
	if (extra_fd == -1)
	{
		dup2(old_stdin, STDIN_FILENO);
		dup2(old_stdout, STDOUT_FILENO);
		close(old_stdin);
		close(old_stdout);
	}
}

int	execute_builtin(t_ast *ast, t_shell *shell, int extra_fd)
{
	int	old_fds[2];
	int	status;

	if (!setup_and_restore_fds(extra_fd, old_fds))
		return (1);
	if (apply_redirections(shell, ast->cmd, extra_fd) == 1)
	{
		restore_fds(extra_fd, old_fds[0], old_fds[1]);
		return (1);
	}
	status = execute_builtin_direct(ast, shell);
	restore_fds(extra_fd, old_fds[0], old_fds[1]);
	return (status);
}
