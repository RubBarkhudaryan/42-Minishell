/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:24:08 by apatvaka          #+#    #+#             */
/*   Updated: 2025/09/23 17:26:44 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

int	ft_exit(char **args)
{
	int	i;

	i = 0;
	if (args_len(args) > 2)
		return (print_helper("minishell: exit: too many arguments\n", NULL), 1);
	if (args_len(args) == 1)
	{
		printf("exit\n");
		exit(0);
	}
	while (args[1][i])
	{
		if (!ft_isdigit(args[1][i]) && args[1][i] != '+' && args[1][i] != '-')
			return (print_helper("minishell: exit: numeric argument required\n",
					NULL), exit(2), 2);
		++i;
	}
	print_helper("exit\n", NULL);
	exit(ft_atoi(args[1]) % 256);
}
