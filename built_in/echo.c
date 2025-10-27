/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:15:00 by apatvaka          #+#    #+#             */
/*   Updated: 2025/10/27 20:44:05 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bulit_in.h"

//	char	*test2[] = {"echo", "-n", "Hello", "World", NULL};

static int	len_of_split(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		++i;
	return (i);
}

int	chek_new_line(char **args, int *is_nl)
{
	int	i;
	int	j;
	int	ret;

	ret = 0;
	i = 0;
	while (args[++i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 1;
		while (args[i][++j] && args[i][j] == 'n')
			;
		if (j == (int)ft_strlen(args[i]))
		{
			ret = i;
			*is_nl = 0;
		}
		else
			break ;
	}
	return (++ret);
}

int	ft_echo(char **args)
{
	int	i;
	int	is_new_line;

	is_new_line = 1;
	if (len_of_split(args) == 1)
		return (print_helper("\n", "minishell: echo: write error "));
	i = chek_new_line(args, &is_new_line);
	while (args[i])
	{
		if (print_helper(args[i], "minishell1: echo: write error "))
			return (1);
		if (args[i + 1])
			if (print_helper(" ", "minishell2: echo: write error "))
				return (1);
		++i;
	}
	if (is_new_line)
		if (print_helper("\n", "minishell3: echo: write error "))
			return (1);
	return (0);
}
