/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:56:54 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/23 17:06:18 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

static int	change_directory(char *path, t_env *env)
{
	char	*cwd;
	char	*old_pwd;

	if (chdir(path) != 0)
	{
		perror("cd: no such file or directory\n");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("cd: PWD not set\n");
		return (1);
	}
	old_pwd = get_value_from_env(env, "PWD");
	if (replace_env_value("OLDPWD", old_pwd, env, 0) || replace_env_value("PWD",
			cwd, env, 0))
	{
		free(cwd);
		return (1);
	}
	free(cwd);
	return (0);
}

int	ft_cd(char **args, t_env *env)
{
	char	*path;

	if (args_len(args) > 2)
	{
		perror("cd: too many arguments\n");
		return (1);
	}
	path = args[1];
	if (!path)
		path = get_value_from_env(env, "HOME");
	if (ft_strcmp(path, "-") == 0)
	{
		path = get_value_from_env(env, "OLDPWD");
		if (!path)
		{
			perror("cd: OLDPWD not set\n");
			return (1);
		}
		printf("%s\n", path);
	}
	return (change_directory(path, env));
}
