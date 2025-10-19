/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:23:30 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/16 23:46:09 by apatvaka         ###   ########.fr       */
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

int	execute_builtin(t_ast *ast, t_shell *shell, int extra_fd)
{
	int	old_stdout;
	int	old_stdin;
	int	status;

	status = 0;
	old_stdout = dup(STDOUT_FILENO);
	old_stdin = dup(STDIN_FILENO);
	if (apply_redirections(shell, ast->cmd, extra_fd) == 1)
		return (1);
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
	return (dup2(old_stdout, STDOUT_FILENO), dup2(old_stdin, STDIN_FILENO),
		close(old_stdout), close(old_stdin), status);
}
