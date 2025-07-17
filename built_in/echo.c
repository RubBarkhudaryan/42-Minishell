/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apatvaka <apatvaka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 12:15:00 by apatvaka          #+#    #+#             */
/*   Updated: 2025/07/17 23:47:56 by apatvaka         ###   ########.fr       */
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
		return (printf("\n"), 0);
	i = 1;
	chek_new_line(args, &is_new_line, &i);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		++i;
	}
	if (is_new_line)
		printf("\n");
	return (0);
}
