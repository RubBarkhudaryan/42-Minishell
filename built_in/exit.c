/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:24:08 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/03 16:10:20 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

static void	exit_helper(char **args, t_shell *shell)
{
	int	i;

	i = 0;
	if (args_len(args) > 2)
	{
		print_helper("minishell: exit: too many arguments\n", NULL);
		exit(1);
	}
	if (args_len(args) == 1)
	{
		print_helper("exit\n", NULL);
		free_shell(shell, 0);
		exit(0);
	}
	while (args[1][++i])
	{
		if (!ft_isdigit(args[1][i]) && args[1][i] != '+' && args[1][i] != '-')
		{
			print_helper("minishell: exit: numeric argument required\n", NULL);
			exit(2);
			free_shell(shell, 0);
		}
	}
}

void	ft_exit(char **args, t_shell *shell)
{
	int	exit_code;

	exit_helper(args, shell);
	exit_code = ft_atoi(args[1]);
	if (exit_code > 255)
		exit_code = exit_code % 256;
	else if (exit_code < 0)
		exit_code = 256 + (exit_code % 256);
	print_helper("exit\n", NULL);
	free_shell(shell, 1);
	exit(exit_code % 256);
}
