/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:23:30 by apatvaka          #+#    #+#             */
/*   Updated: 2025/09/04 18:51:21 by apatvaka         ###   ########.fr       */
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

int	execute_builtin(t_cmd *cmd, t_shell *shell)
{
	int	status;

	if (ft_strcmp(cmd->cmd_name, "cd") == 0)
		status = ft_cd(cmd->args, shell);
	else if (ft_strcmp(cmd->cmd_name, "echo") == 0)
		status = ft_echo(cmd->args);
	else if (ft_strcmp(cmd->cmd_name, "env") == 0)
		status = ft_env(cmd->args, shell);
	else if (ft_strcmp(cmd->cmd_name, "export") == 0)
		status = ft_export(cmd->args, shell);
	else if (ft_strcmp(cmd->cmd_name, "pwd") == 0)
		status = ft_pwd();
	else if (ft_strcmp(cmd->cmd_name, "unset") == 0)
		return (ft_unset(cmd->args, &(shell->env)));
	// else if (ft_strcmp(cmd, "exit") == 0)
	//
	return (status);
}
