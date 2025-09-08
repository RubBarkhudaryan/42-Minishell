/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:56:54 by apatvaka          #+#    #+#             */
/*   Updated: 2025/09/06 15:28:32 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

static int	change_directory(char *path, t_shell *shell)
{
	char	*cwd;
	char	*old_pwd;

	if (chdir(path) != 0)
	{
		errno = 1; // Set errno to 1 for custom error message
		perror("cd: no such file or directory\n");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd: PWD not set\n");
		return (1);
	}
	old_pwd = get_value_from_env(shell->env, "PWD");
	if (replace_env_value("OLDPWD", old_pwd, shell->env)
		|| replace_env_value("PWD", cwd, shell->env))
		return (free(cwd), 1);
	free(cwd);
	return (0);
}

int	ft_cd(char **args, t_shell *shell)
{
	char	*path;

	if (args_len(args) > 2 && args_len(args))
	{
		perror("cd: too many arguments\n");
		return (1);
	}
	path = args[1];
	if (!path)
		path = get_value_from_env(shell->env, "HOME");
	if (ft_strcmp(path, "-") == 0)
	{
		path = get_value_from_env(shell->env, "OLDPWD");
		printf("%s\n", path);
	}
	return (change_directory(path, shell));
}
