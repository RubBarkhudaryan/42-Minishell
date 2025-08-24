/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:23:30 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/24 21:28:29 by apatvaka         ###   ########.fr       */
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
	int	status;

	if (ft_strcmp(cmd, "cd") == 0)
		status = ft_cd(args, env);
	else if (ft_strcmp(cmd, "echo") == 0)
		status = ft_echo(args);
	else if (ft_strcmp(cmd, "env") == 0)
		status = ft_env(args, env);
	else if (ft_strcmp(cmd, "export") == 0)
		status = ft_export(args, &env);
	else if (ft_strcmp(cmd, "pwd") == 0)
		status = ft_pwd(args);
	// else if (ft_strcmp(cmd, "unset") == 0)
	// return (ft_unset(args, env));
	// else if (ft_strcmp(cmd, "exit") == 0)
	return (status);
}
