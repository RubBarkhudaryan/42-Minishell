/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:15:00 by apatvaka          #+#    #+#             */
/*   Updated: 2025/08/17 20:49:53 by apatvaka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "built_in.h"

static int	len_of_split(char **args)
{
	int	i;

	i = 0;
	if (!args || !*args)
		return (0);
	while (args[i])
		++i;
	return (i);
}

void	chek_new_line(char **args, int *is_nl, int *i)
{
	int	j;

	if (args[1][0] == '-' && args[1][1] == 'n')
	{
		*is_nl = 0;
		while (args[*i] && args[*i][0] == '-')
		{
			j = 0;
			while (args[*i][++j])
			{
				if (args[*i][j] != 'n')
				{
					*is_nl = 0;
					return ;
				}
			}
			++(*i);
		}
	}
}

int	ft_echo(char **args)
{
	int	i;
	int	is_new_line;

	is_new_line = 1;
	if (len_of_split(args) == 1)
		return (print_helper("\n", "bash: echo: "));
	i = 1;
	chek_new_line(args, &is_new_line, &i);
	while (args[i])
	{
		if (print_helper(args[i], "bash: echo: "))
			return (1);
		if (args[i + 1])
			if (print_helper(" ", "bash: echo: "))
				return (1);
		++i;
	}
	if (is_new_line)
		if (print_helper("\n", "bash: echo: "))
			return (1);
	return (0);
}
