/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:24:08 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/02 20:00:40 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

void	ft_exit(char **args, t_shell *shell)
{
	int	i;
	int	exit_code;

	i = 0;
	if (args_len(args) > 2)
		return (print_helper("minishell: exit: too many arguments\n", NULL),
			exit(1));
	if (args_len(args) == 1)
	{
		print_helper("exit\n", NULL);
		free_shell(shell, 0);
		exit(0);
	}
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]) && args[1][i] != '+' && args[1][i] != '-')
			return (print_helper("minishell: exit: numeric argument required\n",
					NULL), exit(2), free_shell(shell, 0));
		++i;
	}
	exit_code = ft_atoi(args[1]) % 256;
	print_helper("exit\n", NULL);
	free_shell(shell, 0);
	exit(exit_code % 256);
}
