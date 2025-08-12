/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 11:35:58 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/10 13:27:38 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

int	args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	ft_pwd(char **args) //??
{
	char	*cwd;

	if (args_len(args) > 1 && args_len(args))
	{
		perror("pwd: too many arguments\n");
		return (1);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("pwd: PWD not set\n");
		return (1);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}
