/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:35:58 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/27 09:57:18 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

int	args_len(char **args)
{
	int	i;

	if (!args || !*args)
		return (0);
	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_pwd(t_env *env)
{
	char	*cwd;
	char	*tmp;
	int		flag;

	flag = 0;
	cwd = get_value_from_env(env, "PWD");
	if (!cwd || !*cwd)
	{
		flag = 1;
		cwd = getcwd(NULL, 0);
		if (!cwd)
			return (perror("minishell"), 1);
	}
	tmp = ft_strjoin(cwd, "\n");
	if(flag)
		free(cwd);
	if (!tmp)
		return (perror("minishell"), 1);
	print_helper(tmp, 0);
	free(tmp);
	return (0);
}
