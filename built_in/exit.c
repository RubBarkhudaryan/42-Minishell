/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:24:08 by apatvaka          #+#    #+#             */
/*   Updated: 2025/11/09 13:51:46 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

static void	handle_numeric_error(char *arg, t_shell *shell)
{
	char	*tmp;

	print_helper("exit\n", "minishell: exit");
	tmp = ft_strjoin("minishell: exit: ", arg);
	if (!tmp)
		exit(1);
	ft_putstr_fd(tmp, 2);
	free(tmp);
	ft_putstr_fd(" numeric argument required\n", 2);
	free_shell(shell, 1);
	exit(2);
}

int	ft_in_limit(char *num)
{
	char	*negative;
	char	*positive;

	negative = "-9223372036854775808";
	positive = "9223372036854775807";
	if (*num == '-')
	{
		if (ft_strcmp(negative, num) < 0)
			return (1);
		return (0);
	}
	else
	{
		if (ft_strcmp(positive, num) < 0)
			return (1);
		return (0);
	}
}

static int	check_numeric_arg(char **args, t_shell *shell)
{
	if (!args[1])
		return (0);
	if (!is_valid_numeric_string(args[1]))
	{
		handle_numeric_error(args[1], shell);
	}
	return (0);
}

static int	exit_helper(char **args, t_shell *shell)
{
	if (check_numeric_arg(args, shell))
		return (1);
	if (ft_in_limit(args[1]))
		handle_numeric_error(args[1], shell);
	if (args_len(args) > 2)
	{
		print_helper("exit\n", "minishell: exit");
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (args_len(args) == 1)
	{
		print_helper("exit\n", "minishell: exit");
		free_shell(shell, 1);
		exit(0);
	}
	return (0);
}

int	ft_exit(char **args, t_shell *shell)
{
	int	exit_code;

	exit_code = 0;
	if (exit_helper(args, shell))
	{
		free_shell(shell, 1);
		exit(1);
	}
	exit_code = ft_atoi(args[1]);
	if (exit_code > 255)
		exit_code = exit_code % 256;
	else if (exit_code < 0)
		exit_code = 256 + (exit_code % 256);
	print_helper("exit\n", NULL);
	free_shell(shell, 1);
	exit(exit_code);
}
