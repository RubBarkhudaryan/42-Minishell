/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:56:54 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/01 20:15:51 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

static int	change_directory(char *path, t_shell *shell)
{
	char	*cwd;
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("minishell: cd");
		return (1);
	}
	if (path && chdir(path) != 0)
	{
		free(old_pwd);
		perror("minishell: cd");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("minishell: cd"), free(old_pwd), free(cwd),
			1);
	if (add_or_replace_value(ft_strdup("OLDPWD"), ft_strdup(old_pwd), 0, shell)
		|| add_or_replace_value(ft_strdup("PWD"), ft_strdup(cwd), 0, shell))
		return (free(old_pwd), free(cwd), 1);
	free(cwd);
	free(old_pwd);
	return (0);
}

int	ft_cd(char **args, t_shell *shell)
{
	char	*path;

	if (args_len(args) > 2 && args_len(args))
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	path = args[1];
	if (!path)
		path = get_value_from_env(shell->env, "HOME");
	if (path && ft_strcmp(path, "-") == 0)
	{
		path = get_value_from_env(shell->env, "OLDPWD");
		printf("%s\n", path);
	}
	return (change_directory(path, shell));
}
