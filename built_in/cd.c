/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 10:56:54 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/05 19:11:56 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

static char	*get_old_pwd(t_shell *shell)
{
	char	*old_pwd;
	char	*tmp;

	tmp = get_value_from_env(shell->env, "PWD");
	if (tmp)
	{
		old_pwd = ft_strdup(tmp);
		if (!old_pwd)
			return (NULL);
	}
	else
	{
		old_pwd = getcwd(NULL, 0);
		if (!old_pwd)
		{
			perror("minishell: cd");
			return (NULL);
		}
	}
	return (old_pwd);
}

static int	update_pwd_vars(char *old_pwd, char *cwd, t_shell *shell)
{
	char	*old_pwd_dup;
	char	*cwd_dup;

	old_pwd_dup = ft_strdup(old_pwd);
	cwd_dup = ft_strdup(cwd);
	if (!old_pwd_dup || !cwd_dup)
	{
		free(old_pwd_dup);
		free(cwd_dup);
		return (1);
	}
	if (add_or_replace_value(ft_strdup("OLDPWD"), old_pwd_dup, 0, shell))
	{
		free(cwd_dup);
		return (1);
	}
	if (add_or_replace_value(ft_strdup("PWD"), cwd_dup, 0, shell))
		return (1);
	return (0);
}

static int	change_directory(char *path, t_shell *shell)
{
	char	*old_pwd;
	char	*cwd;

	old_pwd = get_old_pwd(shell);
	if (!old_pwd)
		return (1);
	if (path && chdir(path) != 0)
		return (free(old_pwd), perror("minishell: cd"), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		free(old_pwd);
		perror("minishell: cd");
		return (1);
	}
	if (update_pwd_vars(old_pwd, cwd, shell))
	{
		free(old_pwd);
		free(cwd);
		return (1);
	}
	free(old_pwd);
	free(cwd);
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
